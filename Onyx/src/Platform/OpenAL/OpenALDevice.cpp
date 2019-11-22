#include "onyxpch.h"
#include "OpenALDevice.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <Platform/Windows/WindowsFileIO.h>

namespace Onyx {
	
	OpenALDevice* OpenALDevice::s_Instance = nullptr;
	
	OpenALDevice::OpenALDevice()
	{
		pickALCDevice();


		s_Instance = this;
	}

	OpenALDevice::~OpenALDevice()
	{

	}

	OpenALDevice* OpenALDevice::get()
	{
		if (s_Instance == nullptr)
			return new OpenALDevice();
		else
			return s_Instance;
	}

	void OpenALDevice::pickALCDevice()
	{

		ALCdevice* device = alcOpenDevice(NULL);
		if (!device) {
			printf("OpenALDevice.cpp 39 : OpenAL could not find a sound device\n");
			assert(false);
		}

		ALCcontext* context = alcCreateContext(device, NULL);
		if (!context) {
			printf("OpenALDevice.cpp 45 : OpenAL could not create a sound context\n");
			assert(false);
		}

		alcMakeContextCurrent(context);

		FILE* fp = NULL;
		fopen_s(&fp, "res/audio/theringer1.wav", "rb");

		if (fp == NULL) {
			printf("OpenALDevice.cpp 55 : fp is NULL\n");
			assert(false);
			return;
		}

		char type[4];
		DWORD size, chunksize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, bitsPerSample;
		DWORD dataSize;

		fread(type, sizeof(char), 4, fp);

		if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') {
			printf("OpenALDevice.cpp 64 : WAV file is not RIFF format\n");
			assert(false);
		}

		fread(&size, sizeof(DWORD), 1, fp);
		fread(type, sizeof(char), 4, fp);

		if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') {
			printf("OpenALDevice.cpp 64 : Not a .WAV file\n");
			assert(false);
		}

		fread(type, sizeof(char), 4, fp);

		if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ') {
			printf("OpenALDevice.cpp 64 : Not fmt\n");
			assert(false);
		}

		fread(&chunksize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&bitsPerSample, sizeof(short), 1, fp);


		//seek further to data
		fseek(fp, 0x24, 0);
		fread(type, sizeof(char), 4, fp);

		if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a') {
			printf("OpenALDevice.cpp 64 : Missing WAV data\n");
			assert(false);
		}

		fread(&dataSize, sizeof(DWORD), 1, fp);

		//allocate WAV data to the heap
		unsigned char* wavBuff = new unsigned char[dataSize];

		fread(wavBuff, sizeof(char), dataSize, fp);

		//source 
		ALuint source;
		ALuint buffer;
		ALuint frequency = sampleRate;
		ALenum format = 0;

		alGenBuffers(1, &buffer);
		alGenSources(1, &source);

		if (bitsPerSample == 8) {
			if (channels == 1)
				format = AL_FORMAT_MONO8;
			else if (channels == 2)
				format = AL_FORMAT_STEREO8;
		}
		else if (bitsPerSample == 16) {
			if (channels == 1)
				format = AL_FORMAT_MONO16;
			else if (channels == 2)
				format = AL_FORMAT_STEREO16;
		}

		//submit to buffer
		alBufferData(buffer, format, wavBuff, dataSize, frequency);
		
		ALfloat sourcePos[] = { 0.0f,0.0f,0.0f };
		ALfloat sourceVel[] = { 0.0f,0.0f,0.0f };
		ALfloat listenerPos[] = { 0.0f,0.0f,0.0f };
		ALfloat listenerVel[] = { 0.0f,0.0f,0.0f };

		//2d vector pointing towards the listeners view and also upwards
		ALfloat listenerOri[] = { 0.0f,0.0f,-1.0f, 0.0f, 1.0f, 0.0f };

		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);

		alSourcei(source, AL_BUFFER, buffer);
		alSourcef(source, AL_PITCH, 1.0f);
		alSourcef(source, AL_GAIN, 1.0f);
		alSourcefv(source, AL_POSITION, sourcePos);
		alSourcefv(source, AL_VELOCITY, sourceVel);
		alSourcei(source, AL_LOOPING, false);

		alSourcePlay(source);
		//alSourcePause(source);
		//alSourceStop(source);
	}

}
