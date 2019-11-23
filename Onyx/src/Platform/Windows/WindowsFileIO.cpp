#include "onyxpch.h"
#include "WindowsFileIO.h"

#include <fstream>



namespace Onyx {

	FileIO* FileIO::s_Instance = new WindowsFileIO();

	const std::string WindowsFileIO::readFileStringImplementation(const std::string& filepath)
	{
		
		FILE* file;
		fopen_s(&file, filepath.c_str(), "rt");

		if (!file) {
			printf("Can not open file, invalid file path!\n");
			if(file != NULL)
				fclose(file);
			return "";
		}


		fseek(file, 0, SEEK_END);
		unsigned long length = (unsigned long)ftell(file);
		
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	const std::vector<char> WindowsFileIO::readFileByteImplementation(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error opening file readFileByteImplementation()\n";
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;

	}

	void WindowsFileIO::getFileNameWithoutExtensionImplementation(std::string& filepath)
	{

		const size_t last_slash_idx = filepath.find_last_of("\\/");
		if (std::string::npos != last_slash_idx)
			filepath.erase(0, last_slash_idx + 1);

		const size_t period_idx = filepath.rfind('.');
		if (std::string::npos != period_idx)
			filepath.erase(period_idx);
	}

}