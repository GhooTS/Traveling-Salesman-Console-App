#pragma once


#include <vector>
#include <tbb/tbb.h>




namespace TSP
{
	class FitnessFunction
	{
	public:
		static void fitnessFunction(std::vector<int>& indiv, std::vector<std::vector<int>>& matrixDistance)
		{
			int from = 0;
			int to = 0;

			indiv.back() = 0;

			for (size_t j = 1; j < indiv.size() - 1; j++)
			{
				from = indiv[j - 1];
				to = indiv[j];

				indiv.back() += matrixDistance.at(from)[to];
			}
			from = to;
			to = indiv[0];
			indiv.back() += matrixDistance.at(from)[to];
		}
	};
}
