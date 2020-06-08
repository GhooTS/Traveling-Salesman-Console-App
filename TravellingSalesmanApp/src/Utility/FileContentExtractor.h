#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>




namespace Utility 
{

	inline std::vector<std::string> getFileContent(std::string path)
	{
		std::ifstream fileToRead(path);


		if (fileToRead) 
		{
			std::vector<std::string> output;
			std::string line;
			int i = 0;

			while (getline(fileToRead, line))
			{
				output.push_back(line);
			}

			fileToRead.close();
			return output;
		}
		else 
		{
			throw runtime_error("invliade file path");
		}
		
	}
}