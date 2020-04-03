#pragma once


#include <tbb/tbb.h>
#include <vector>
#include "Mutator.h"
#include "FittnessFunction.h"
#include "Crossover.h"

namespace TSP
{
	using namespace std;

	class TSPJob
	{
		vector<vector<int>>& indiv;
		vector<vector<int>>& nextGeneration;
		vector<vector<int>>& matrixDistance;
		vector<int>& selection;
		double copyChance;
		double mutationChance;

	public:
		void operator()(tbb::blocked_range<size_t> range)const
		{


			int index = 0;

			for (size_t i = range.begin(); i != range.end(); ++i)
			{

				index = i * 2;
				if (index > indiv.size())
				{
					break;
				}

				//Crossover
				TSP::Crossover::crossPair(copyChance, indiv[selection[index]], indiv[selection[index + 1]],
					nextGeneration[index], nextGeneration[index + 1]);

				//Mutation
				TSP::Mutator::mutateInversion(nextGeneration[index], mutationChance);
				TSP::Mutator::mutateInversion(nextGeneration[index + 1], mutationChance);

				//FitnessFunction
				TSP::FitnessFunction::fitnessFunction(nextGeneration[index], matrixDistance);
				TSP::FitnessFunction::fitnessFunction(nextGeneration[index + 1], matrixDistance);
			}

			if (index > 0 && index % 2 != 0)
			{
				copy(indiv[selection[index]].begin(), indiv[selection[index]].end(), nextGeneration[index].begin());
			}
		}

		TSPJob(double copyChance, double mutationChance, std::vector<std::vector<int>>& indiv, std::vector<std::vector<int>>& nextGen, std::vector<std::vector<int>>& matrixDistance, std::vector<int>& selection)
			: copyChance(copyChance), mutationChance(mutationChance), indiv(indiv), nextGeneration(nextGen), matrixDistance(matrixDistance), selection(selection)
		{}
	};
}