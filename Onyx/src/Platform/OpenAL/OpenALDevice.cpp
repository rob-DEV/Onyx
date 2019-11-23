#include "onyxpch.h"
#include "OpenALDevice.h"


namespace Onyx {
	
	OpenALDevice* OpenALDevice::s_Instance = nullptr;
	
	OpenALDevice::OpenALDevice()
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

		s_Instance = this;
	}

	OpenALDevice::~OpenALDevice()
	{
		alcCloseDevice(m_Device);
		alcDestroyContext(m_Context);
	}

	OpenALDevice* OpenALDevice::get()
	{
		if (s_Instance == nullptr)
			return new OpenALDevice();
		else
			return s_Instance;
	}


}
