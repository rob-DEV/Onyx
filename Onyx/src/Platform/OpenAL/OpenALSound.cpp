#include "onyxpch.h"
#include "OpenALSound.h"

#include <Platform/Windows/WindowsFileIO.h>

namespace Onyx {

	OpenALSound::OpenALSound(const std::string& filePath)
	{

		m_FilePath = filePath;
		m_Name = filePath;

		FileIO::GetFileNameWithoutExtension(m_Name);

		FILE* fp = NULL;
		fopen_s(&fp, filePath.c_str(), "rb");

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

		ALuint frequency = sampleRate;
		ALenum format = 0;

		alGenBuffers(1, &m_Buffer);
		alGenSources(1, &m_Source);

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
		alBufferData(m_Buffer, format, wavBuff, dataSize, frequency);
		delete[] wavBuff;

		ALfloat sourcePos[] = { 0.0f,0.0f,0.0f };
		ALfloat sourceVel[] = { 0.0f,0.0f,0.0f };
		ALfloat listenerPos[] = { 0.0f,0.0f,0.0f };
		ALfloat listenerVel[] = { 0.0f,0.0f,0.0f };

		//2d vector pointing towards the listeners view and also upwards
		ALfloat listenerOri[] = { 0.0f,0.0f,-1.0f, 0.0f, 1.0f, 0.0f };

		alListenerfv(AL_POSITION, listenerPos);
		
		alListenerfv(AL_ORIENTATION, listenerOri);

		alSourcei(m_Source, AL_BUFFER, m_Buffer);
		alSourcef(m_Source, AL_PITCH, 1.0f);
		alSourcef(m_Source, AL_GAIN, .05f);
		alSourcefv(m_Source, AL_POSITION, sourcePos);
		alSourcefv(m_Source, AL_VELOCITY, sourceVel);
		alSourcei(m_Source, AL_SOURCE_RELATIVE, AL_FALSE);

	}

	OpenALSound::~OpenALSound()
	{
		Stop();
	}

	void OpenALSound::Play()
	{
		alSourcei(m_Source, AL_LOOPING, false);
		alSourcePlay(m_Source);
		m_IsPlaying = true;
	}

	void OpenALSound::Loop()
	{
		alSourcei(m_Source, AL_LOOPING, true);
		alSourcePlay(m_Source);
		m_IsPlaying = true;
	}

	void OpenALSound::Pause()
	{
		alSourcePause(m_Source);
		m_IsPlaying = false;
	}

	void OpenALSound::Resume()
	{
		if (!m_IsPlaying) {
			alSourcePlay(m_Source);
			m_IsPlaying = true;
		}
	}

	void OpenALSound::Stop()
	{
		alSourceStop(m_Source);
		m_IsPlaying = false;
		alDeleteSources(1, &m_Source);
		alDeleteBuffers(1, &m_Buffer); 
	}

	void OpenALSound::SetGain(float gain)
	{
		m_Gain = std::clamp(gain, 0.0f, 5.0f);
		alSourcef(m_Source, AL_GAIN, m_Gain);
	}

	void OpenALSound::LoadWavFile()
	{

	}

}