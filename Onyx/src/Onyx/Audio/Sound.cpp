#include "onyxpch.h"
#include "Sound.h"

namespace Onyx {

	Sound::Sound(std::string& filePath)
	{

	}

	Sound::~Sound()
	{

	}

	void Sound::play()
	{
		m_IsPlaying = true;
	}

	void Sound::loop()
	{

	}

	void Sound::pause()
	{

	}

	void Sound::resume()
	{

	}

	void Sound::stop()
	{

	}

	void Sound::setGain(float gain)
	{
		std::clamp(gain, 0.0f, 1.0f); m_Gain = gain;
	}

}