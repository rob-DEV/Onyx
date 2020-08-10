#ifndef _ONYX_PLATFORM_WINDOWS_FILEIO_H_
#define _ONYX_PLATFORM_WINDOWS_FILEIO_H_

#include <Onyx/Core/Input.h>
#include <Onyx/core/FileIO.h>


namespace Onyx {

	class WindowsFileIO : public FileIO {

	public:
		const std::string readFileStringImplementation(const std::string& filepath);
		const std::vector<char> readFileByteImplementation(const std::string& filepath);
		void getFileNameWithoutExtensionImplementation(std::string& filepath);
	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_FILEIO_H_
