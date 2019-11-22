#ifndef _ONYX_AUDIO_SOUND_H_
#define _ONYX_AUDIO_SOUND_H_

#include <Onyx/core/Core.h>
#include <string>

namespace Onyx {

	class ONYX_API Sound {
	public:
		Sound(std::string& filePath);
		~Sound();
	
		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setGain(float gain);
		inline float getGain() const { return m_Gain; };
		inline bool isPlaying() const { return m_IsPlaying; };

	private:
		std::string m_Name;
		std::string m_FilePath;
		float m_Gain;
		bool m_IsPlaying = false;

	};

}


#endif // !_ONYX_AUDIO_SOUND_H_
