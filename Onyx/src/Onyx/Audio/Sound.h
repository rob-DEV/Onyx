#ifndef _ONYX_AUDIO_SOUND_H_
#define _ONYX_AUDIO_SOUND_H_

#include <Onyx/core/Core.h>
#include <string>

namespace Onyx {

	class ONYX_API Sound {
	public:
		virtual ~Sound() = default;

		virtual void Play() = 0;
		virtual void Loop() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Stop() = 0;

		virtual void SetGain(float gain) = 0;
		inline float GetGain() const { return m_Gain; };
		inline bool IsPlaying() const { return m_IsPlaying; };
		inline const std::string& GetName() const { return m_Name; };
	protected:
		std::string m_Name;
		std::string m_FilePath;
		float m_Gain = 1.0;
		bool m_IsPlaying = false;


	};

	class SoundDevice {
	public:
		inline static void Init() { s_Instance->InitImplementation(); };
		inline static void Destroy() { s_Instance->DestroyImplementation(); };
	protected:
		virtual void InitImplementation() = 0;
		virtual void DestroyImplementation() = 0;
	private:
		static SoundDevice* s_Instance;
	};

}


#endif // !_ONYX_AUDIO_SOUND_H_
