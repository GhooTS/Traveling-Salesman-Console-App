#pragma once

#include <vector>
#include <iostream>
#include "StringUtility.h"

using namespace Utility;

namespace TSP 
{

	static class MatrixGenerator
	{
	public:
		static std::vector<std::vector<int>> genrate(std::vector<std::string>& str,bool symetricMatrix)
		{
			bool isSymetric = false;
			std::vector<std::string>::iterator iterator;
			iterator = str.begin();

			std::string firstline = *iterator;

			size_t size = stoi(firstline); // get matrix size from first line

			std::vector<std::vector<int>> output(size, std::vector<int>(size));

			for (int i = 0; i < size; i++)
			{
				std::string line = *++iterator;
				line = trim(line, " ");
				std::vector<std::string> spliteLine = splite(line, " ");


				//Check for if row length is smaller or equal column length
				if (spliteLine.size() > size)
				{
					throw std::runtime_error(string("Format Exception: size of matrix row is bigger then size of column"));
				}

				for (size_t j = 0; j < spliteLine.size(); j++)
				{
					output[i][j] = stoi(spliteLine.at(j));
				}
			}


			if (symetricMatrix) {
				makeSymmetricMatrix(output, size);
			}


			return output;
		}

		static void makeSymmetricMatrix(std::vector<std::vector<int>>& matrix, const size_t size)
		{
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = i + 1; j < size; j++)
				{
					matrix[i][j] = matrix[j][i];
				}
			}
		}
	};
}
