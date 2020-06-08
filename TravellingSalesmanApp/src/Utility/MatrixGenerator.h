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
		static std::vector<std::vector<int>> generate(std::vector<std::string>& str,bool symetricMatrix)
		{
			bool isSymetric = false;
			size_t size = 0;
			std::vector<std::string>::iterator iterator;
			iterator = str.begin();

			std::string firstline = *iterator;

			try 
			{
				size = stoi(firstline); // get matrix size from first line
			}
			catch (std::invalid_argument& exp) 
			{
				throw std::runtime_error("Format Exception: specify number of rows is incorrect");
			}
			catch (std::out_of_range& exp) 
			{
				throw std::runtime_error("Format Exception: specify number of rows is incorrect");
			}

			size_t lastRowSize = symetricMatrix ? 1 : size;

			std::vector<std::vector<int>> output(size, std::vector<int>(size));

			for (int i = 0; i < size; i++)
			{
				std::string line = *++iterator;
				line = trim(line, " ");
				std::vector<std::string> spliteLine = splite(line, " ");

				if (spliteLine.size() != lastRowSize) 
				{
					std::cout << lastRowSize << std::endl;
					std::cout << spliteLine.size() << std::endl;
					//throw std::runtime_error("Format Exception: content of supplay file is incorect");
				}

				if (symetricMatrix) lastRowSize = spliteLine.size() + 1;

				//Check if row length is smaller or equal to column length
				if (spliteLine.size() > size)
				{
					throw std::runtime_error(string("Format Exception: size of matrix row is bigger then size of column"));
				}

				for (size_t j = 0; j < spliteLine.size(); j++)
				{
					try
					{
						output[i][j] = stoi(spliteLine.at(j));
					}
					catch (std::invalid_argument& exp)
					{
						throw std::runtime_error(string("Format Exception: value in row " + to_string(i) + " and column" + to_string(j) + " is incorrect"));
					}
					catch (std::out_of_range& exp)
					{
						throw std::runtime_error(string("Format Exception: value in row " + to_string(i) + " and column" + to_string(j) + " is incorrect"));
					}
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
