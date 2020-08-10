#ifndef _ONYX_AUDIO_SOUND_MANAGER_H_
#define _ONYX_AUDIO_SOUND_MANAGER_H_

#include <Onyx/core/Core.h>
#include "Sound.h"

#include <unordered_map>
#include <string>

namespace Onyx {

	class ONYX_API SoundManager {	
	public:
		static void init();
		static void add(const std::string& fileName); //TODO check sound name against map for caching purposes
		static void remove();
		static Sound* getSound();

	private:
		std::unordered_map<std::string, Sound*> m_Sounds;
	};



}


#endif // !_ONYX_AUDIO_SOUND_H_
