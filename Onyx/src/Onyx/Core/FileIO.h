#ifndef _ONYX_FILEIO_H_
#define _ONYX_FILEIO_H_

#include "Core.h"
#include <string>
#include <vector> 

namespace Onyx {

	class ONYX_API FileIO {

	public:
		inline static std::string ReadFileString(std::string_view filepath) { return s_Instance->ReadFileStringImplementation(filepath); };
		inline static std::vector<char> ReadFileByte(std::string_view filepath) { return s_Instance->ReadFileByteImplementation(filepath); };
		inline static void GetFileNameWithoutExtension(std::string& filePath) { return s_Instance->GetFileNameWithoutExtensionImplementation(filePath); };
		inline static const std::string GetFileExtension(const  std::string& filePath) { return s_Instance->GetFileExtensionImplementation(filePath); };



	protected:
		virtual const std::string ReadFileStringImplementation(std::string_view filepath) = 0;
		virtual const std::vector<char> ReadFileByteImplementation(std::string_view filepath) = 0;
		virtual void GetFileNameWithoutExtensionImplementation(std::string& filepath) = 0;
		virtual const std::string GetFileExtensionImplementation(std::string_view filepath) = 0;
	private:
		static FileIO* s_Instance;

	};

}

#endif // !_ONYX_FILEIO_H_