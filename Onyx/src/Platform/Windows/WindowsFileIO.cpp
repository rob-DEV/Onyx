#include "onyxpch.h"

#include "WindowsFileIO.h"
#include <fstream>

namespace Onyx {

	FileIO* FileIO::s_Instance = new WindowsFileIO();

	const std::string WindowsFileIO::ReadFileStringImplementation(std::string_view filepath)
	{
		
		FILE* file;
		fopen_s(&file, filepath.data(), "rt");

		if (!file) {
			printf("Can not open file, invalid file path!\n");
			if(file != NULL)
				fclose(file);
			return "";
		}

		fseek(file, 0, SEEK_END);
		uint64_t length = (unsigned long)ftell(file);
		
		char* data = new char[uint64_t(length) + uint64_t(1)];
		memset(data, 0, length + uint64_t(1));
		
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	const std::vector<char> WindowsFileIO::ReadFileByteImplementation(std::string_view filepath)
	{
		std::ifstream file(filepath.data(), std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error opening file readFileByteImplementation()\n";
			assert(false);
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;

	}

	void WindowsFileIO::GetFileNameWithoutExtensionImplementation(std::string& filepath)
	{

		const size_t last_slash_idx = filepath.find_last_of("\\/");
		if (std::string::npos != last_slash_idx)
			filepath.erase(0, last_slash_idx + 1);

		const size_t period_idx = filepath.rfind('.');
		if (std::string::npos != period_idx)
			filepath.erase(period_idx);
	}

	const std::string WindowsFileIO::GetFileExtensionImplementation(std::string_view filePath)
	{
		return filePath.substr(filePath.find_last_of(".") + 1).data();
	}

}