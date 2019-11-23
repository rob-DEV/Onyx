#ifndef _ONYX_AUDIO_SOUND_H_
#define _ONYX_AUDIO_SOUND_H_

#include <Onyx/core/Core.h>
#include <string>

namespace Onyx {

	class ONYX_API Sound {
	public:
		virtual ~Sound() = default;

		virtual void play() = 0;
		virtual void loop() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
		virtual void stop() = 0;

		virtual void setGain(float gain) = 0;
		inline float getGain() const { return m_Gain; };
		inline bool isPlaying() const { return m_IsPlaying; };
		inline const std::string& getName() const { return m_Name; };
	protected:
		std::string m_Name;
		std::string m_FilePath;
		float m_Gain = 1.0;
		bool m_IsPlaying = false;


	};

	class SoundDevice {
	public:
		inline static void init() { s_Instance->initImplementation(); };
		inline static void destroy() { s_Instance->destroyImplementation(); };
	protected:
		virtual void initImplementation() = 0;
		virtual void destroyImplementation() = 0;
	private:
		static SoundDevice* s_Instance;
	};

}


#endif // !_ONYX_AUDIO_SOUND_H_
