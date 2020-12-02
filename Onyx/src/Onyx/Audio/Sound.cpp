#include "onyxpch.h"
#include "Sound.h"

#include <Platform/OpenAL/OpenALSound.h>

namespace Onyx {

	Sound* Sound::Create(std::string_view filePath)
	{
		//currently only supporting OpenAL 
		return new OpenALSound(filePath);

	}

}