#ifndef _ONYX_PLATFORM_OPENAL_DEVICE_H_
#define _ONYX_PLATFORM_OPENAL_DEVICE_H_

#include <AL/al.h>
#include <AL/alc.h>

#include <Onyx/Audio/Sound.h>

namespace Onyx {
	
	class OpenALDevice : public SoundDevice {

	public:
		OpenALDevice();
		~OpenALDevice();
		virtual void InitImplementation();
		virtual void DestroyImplementation();
		ALCdevice* GetNativeDevice() { return m_Device; };

	private:
		ALCdevice* m_Device = nullptr;
		ALCcontext* m_Context = nullptr;


	};

}


#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
