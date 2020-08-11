#include "onyxpch.h"
#include "Sound.h"

#include <Platform/OpenAL/OpenALSound.h>

namespace Onyx {

	Sound* Sound::Create(const std::string& filePath)
	{
		//currently only supporting OpenAL 
		return new OpenALSound(filePath);

	}

}