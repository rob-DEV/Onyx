#include "onyxpch.h"
#include "OpenALDevice.h"


namespace Onyx {
	
	SoundDevice* SoundDevice::s_Instance = new OpenALDevice();
	
	OpenALDevice::OpenALDevice()
	{

	}

	OpenALDevice::~OpenALDevice()
	{

	}

	void OpenALDevice::InitImplementation()
	{
		m_Device = alcOpenDevice(NULL);
		if (!m_Device) {
			printf("OpenALDevice.cpp 13 : OpenAL could not find a sound device\n");
			assert(false);
		}

		m_Context = alcCreateContext(m_Device, NULL);
		if (!m_Context) {
			printf("OpenALDevice.cpp 19 : OpenAL could not create a sound context\n");
			assert(false);
		}
		alcMakeContextCurrent(m_Context);

	}

	void OpenALDevice::DestroyImplementation()
	{
		alcCloseDevice(m_Device);
		alcDestroyContext(m_Context);
	}

}
