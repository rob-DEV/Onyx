#ifndef _ONYX_FILEIO_H_
#define _ONYX_FILEIO_H_

#include "Core.h"
#include <string>

namespace Onyx {

	class ONYX_API FileIO {

	public:
		inline static std::string readFile(const std::string& filepath) { return s_Instance->readFileImplementation(filepath); };

	protected:
		virtual const std::string readFileImplementation(const std::string& filepath) = 0;

	private:
		static FileIO* s_Instance;
	};
}

#endif // !_ONYX_FILEIO_H_