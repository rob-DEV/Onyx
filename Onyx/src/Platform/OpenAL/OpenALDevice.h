#ifndef _ONYX_PLATFORM_OPENAL_DEVICE_H_
#define _ONYX_PLATFORM_OPENAL_DEVICE_H_

#include <AL/al.h>
#include <AL/alc.h>

namespace Onyx {
	
	class OpenALDevice {

	private:
		OpenALDevice();
		static OpenALDevice* s_Instance;
	public:
		~OpenALDevice();
		static OpenALDevice* get();
		ALCdevice* getALCDevice() { return m_Device; };

	private:
		ALCdevice* m_Device = nullptr;
		ALCcontext* m_Context = nullptr;


	};

}


#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
