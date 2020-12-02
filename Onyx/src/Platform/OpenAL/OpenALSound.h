#ifndef _ONYX_PLATFORM_OPENAL_SOUND_H_
#define _ONYX_PLATFORM_OPENAL_SOUND_H_

#include <Onyx/Audio/Sound.h>
#include "OpenALDevice.h"

namespace Onyx {

	class OpenALSound : public Sound {

	public:
		OpenALSound(std::string_view filePath);
		~OpenALSound();

		virtual void Play();
		virtual void Loop();
		virtual void Pause();
		virtual void Resume();
		virtual void Stop();

		virtual void SetGain(float gain);
		virtual ALuint GetSource() const { return m_Source; };

	private:
		ALuint m_Source;
		ALuint m_Buffer;

		void LoadWavFile();

	};

}


#endif // !_ONYX_PLATFORM_OPENGL_BUFFER_H_
