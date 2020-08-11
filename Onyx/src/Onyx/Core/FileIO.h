#ifndef _ONYX_FILEIO_H_
#define _ONYX_FILEIO_H_

#include "Core.h"
#include <string>
#include <vector> 

namespace Onyx {

	class ONYX_API FileIO {

	public:
		inline static std::string ReadFileString(const std::string& filepath) { return s_Instance->ReadFileStringImplementation(filepath); };
		inline static std::vector<char> ReadFileByte(const std::string& filepath) { return s_Instance->ReadFileByteImplementation(filepath); };
		inline static void GetFileNameWithoutExtension(std::string& filePath) { return s_Instance->GetFileNameWithoutExtensionImplementation(filePath); };
	protected:
		virtual const std::string ReadFileStringImplementation(const std::string& filepath) = 0;
		virtual const std::vector<char> ReadFileByteImplementation(const std::string& filepath) = 0;
		virtual void GetFileNameWithoutExtensionImplementation(std::string& filepath) = 0;
	private:
		static FileIO* s_Instance;

	};

}

#endif // !_ONYX_FILEIO_H_