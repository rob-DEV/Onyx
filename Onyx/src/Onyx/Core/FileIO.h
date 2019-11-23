#ifndef _ONYX_FILEIO_H_
#define _ONYX_FILEIO_H_

#include "Core.h"
#include <string>
#include <vector> 

namespace Onyx {

	class ONYX_API FileIO {

	public:
		inline static std::string readFileString(const std::string& filepath) { return s_Instance->readFileStringImplementation(filepath); };
		inline static std::vector<char> readFileByte(const std::string& filepath) { return s_Instance->readFileByteImplementation(filepath); };
		inline static void getFileNameWithoutExtension(std::string& filePath) { return s_Instance->getFileNameWithoutExtensionImplementation(filePath); };
	protected:
		virtual const std::string readFileStringImplementation(const std::string& filepath) = 0;
		virtual const std::vector<char> readFileByteImplementation(const std::string& filepath) = 0;
		virtual void getFileNameWithoutExtensionImplementation(std::string& filepath) = 0;
	private:
		static FileIO* s_Instance;

	};

}

#endif // !_ONYX_FILEIO_H_