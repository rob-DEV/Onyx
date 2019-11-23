#ifndef _ONYX_PLATFORM_OPENAL_SOUND_H_
#define _ONYX_PLATFORM_OPENAL_SOUND_H_

#include <Onyx/Audio/Sound.h>
#include "OpenALDevice.h"

namespace Onyx {

	class OpenALSound : public Sound {

	public:
		OpenALSound(const std::string& filePath);
		~OpenALSound();

		virtual void play();
		virtual void loop();
		virtual void pause();
		virtual void resume();
		virtual void stop();

		virtual void setGain(float gain);
		virtual ALuint getSource() const { return m_Source; };

	private:
		ALuint m_Source;
		ALuint m_Buffer;

		void loadWavFile();

	};

}


#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
