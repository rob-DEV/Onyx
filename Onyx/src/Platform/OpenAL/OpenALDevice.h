#ifndef _ONYX_PLATFORM_OPENAL_DEVICE_H_
#define _ONYX_PLATFORM_OPENAL_DEVICE_H_

#include <Onyx/graphics/Buffer.h>

namespace Onyx {
	
	class OpenALDevice {

	private:
		OpenALDevice();
		static OpenALDevice* s_Instance;
	public:
		~OpenALDevice();
		static OpenALDevice* get();
		

	private:
		void pickALCDevice();

	};


}



#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
