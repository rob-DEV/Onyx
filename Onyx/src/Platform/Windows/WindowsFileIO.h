#ifndef _ONYX_PLATFORM_WINDOWS_FILEIO_H_
#define _ONYX_PLATFORM_WINDOWS_FILEIO_H_

#include <Onyx/core/Input.h>
#include <Onyx/core/FileIO.h>


namespace Onyx {

	class WindowsFileIO : public FileIO {

	public:
		const std::string readFileImplementation(const std::string& filepath);

	};

}


#endif // !_ONYX_PLATFORM_WINDOWS_FILEIO_H_
