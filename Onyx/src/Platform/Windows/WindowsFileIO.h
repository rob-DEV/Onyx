#ifndef _ONYX_PLATFORM_WINDOWS_FILEIO_H_
#define _ONYX_PLATFORM_WINDOWS_FILEIO_H_

#include <Onyx/Core/Input.h>
#include <Onyx/core/FileIO.h>


namespace Onyx {

	class WindowsFileIO : public FileIO {

	public:
		const std::string ReadFileStringImplementation(const std::string& filepath);
		const std::vector<char> ReadFileByteImplementation(const std::string& filepath);
		void GetFileNameWithoutExtensionImplementation(std::string& filepath);
	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_FILEIO_H_
