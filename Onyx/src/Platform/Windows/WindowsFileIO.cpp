#include "onyxpch.h"
#include "WindowsFileIO.h"

#include <fstream>

namespace Onyx {

	FileIO* FileIO::s_Instance = new WindowsFileIO();

	const std::string WindowsFileIO::readFileImplementation(const std::string& filepath)
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
		unsigned int length = (unsigned int)ftell(file);
		
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

}