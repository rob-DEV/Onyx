#ifndef _ONYX_PLATFORM_WINDOWS_FILEIO_H_
#define _ONYX_PLATFORM_WINDOWS_FILEIO_H_

#include <Onyx/Core/Input.h>
#include <Onyx/core/FileIO.h>


namespace Onyx {

	class WindowsFileIO : public FileIO {

	public:
		const std::string ReadFileStringImplementation(std::string_view filepath);
		const std::vector<char> ReadFileByteImplementation(std::string_view filepath);
		void GetFileNameWithoutExtensionImplementation(std::string& filepath);
		const std::string GetFileExtensionImplementation(std::string_view filePath);
	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_FILEIO_H_
