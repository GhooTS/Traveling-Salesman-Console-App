#pragma once

#include <vector>
#include <iostream>
#include "StringUtility.h"

using namespace Utility;

namespace TSP 
{

	struct vector2
	{
		int x;
		int y;

		vector2(int x, int y)
			:x(x),y(y)
		{
			
		}

	public:

		static int getDistance(vector2 from,vector2 to)
		{
			return sqrt(pow(to.x - from.x,2) + pow(to.y - from.y, 2));
		}
	};

	static class MatrixGenerator
	{
	public:

		static std::vector<std::vector<int>> generate(std::vector<std::string>& str,bool calculatefromPosition = false)
		{
			bool isSymetric = false;
			size_t size = 0;

			try 
			{
				size = stoi(str.front()); // get matrix size from first line
			}
			catch (std::invalid_argument& exp) 
			{
				throw std::runtime_error("Format Exception: specify number of rows is incorrect");
			}
			catch (std::out_of_range& exp) 
			{
				throw std::runtime_error("Format Exception: specify number of rows is incorrect");
			}

			std::vector<std::vector<int>> output(size, std::vector<int>(size));


			if (calculatefromPosition) 
			{
				auto position = GetPosition(str,size);
				createMatrix(position, output);
			}
			else 
			{
				createMatrix(str, output);
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

		/// <summary>
		/// Create matrix from position
		/// </summary>
		/// <param name="position"></param>
		/// <param name="matrix"></param>
		static void createMatrix(std::vector<vector2>& position, std::vector<std::vector<int>>& matrix)
		{

			for (size_t x = 0; x < position.size(); x++)
			{
				for (size_t y = 0; y < position.size(); y++)
				{
					matrix[x][y] = vector2::getDistance(position[x], position[y]);
				}
			}
		}

		/// <summary>
		/// Create matrix from text
		/// </summary>
		/// <param name="rows"></param>
		/// <param name="matrix"></param>
		static void createMatrix(std::vector<string>& rows, std::vector<std::vector<int>>& matrix)
		{

			bool symetricMatrix = trim(rows[1]," ").size() != matrix.size();

			size_t lastRowSize = symetricMatrix ? 1 : matrix.size();

			for (int i = 1; i < matrix.size() + 1; i++)
			{
				std::string line = trim(rows[i], " ");
				std::vector<std::string> spliteLine = splite(line, " ");

				if (spliteLine.size() != lastRowSize)
				{
					throw std::runtime_error("Format Exception: content of supplay file is incorect");
				}

				if (symetricMatrix) lastRowSize = spliteLine.size() + 1;

				//Check if row length is smaller or equal to column length
				if (spliteLine.size() > matrix.size())
				{
					throw std::runtime_error(string("Format Exception: size of matrix row is bigger then size of column"));
				}

				for (size_t j = 0; j < spliteLine.size(); j++)
				{
					try
					{
						matrix[i - 1][j] = stoi(spliteLine.at(j));
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

			if (symetricMatrix) 
			{
				makeSymmetricMatrix(matrix, matrix.size());
			}
		}


		/// <summary>
		/// Converts text to position
		/// </summary>
		/// <param name="rows"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		static std::vector<vector2> GetPosition(std::vector<std::string>& rows,size_t size) 
		{
			std::vector<vector2> output;
			output.reserve(size);

			for (size_t i = 1; i < size + 1; i++)
			{
				auto spliteLine = Utility::splite(rows[i]," ");

				if (spliteLine.size() < 2 || spliteLine.size() > 3)
				{
					throw std::runtime_error(string("Format Exception: the position are incorrect"));
				}

				auto x = stoi(spliteLine.size() == 2 ? spliteLine[0] : spliteLine[1]);
				auto y = stoi(spliteLine.size() == 2 ? spliteLine[1] : spliteLine[2]);
				output.push_back(vector2(x, y));
			}

			return output;
		}
	};
}
