#ifndef _ONYX_RESOURCES_HASHER_H_
#define _ONYX_RESOURCES_HASHER_H_

#include <Onyx/Core/Core.h>
#include <string>
#include <chrono>

namespace Onyx {

	//Internal hashing class for file paths & strings
	class Hasher {
	public:
		inline static uint64_t HashString(const std::string& str) {

			uint64_t hash = 0x811c9dc5;
			uint64_t prime = 0x1000193;
			for (int i = 0; i < str.size(); ++i) {
				uint8_t value = str[i];
				hash = hash ^ value;
				hash *= prime;
			}

			return hash;
		}

		inline static std::string LongToString(uint64_t val) {
			return std::to_string(val);
		}

		inline static std::string GenerateUniqueID() {
			
			static uint64_t seed = 0x50869A9;

			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				);

			seed += ms.count();

			return LongToString(seed << 2);
		}
	};

}

#endif // !_ONYX_RESOURCES_HASHER_H_
