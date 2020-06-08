#pragma once


#include <tbb/tbb.h>
#include <vector>
#include "Operation/Mutator.h"
#include "Operation/FittnessFunction.h"
#include "Operation/Crossover.h"
#include "TSPData.h"
#include "TSPConfig.h"

namespace TSP
{

	class TSPJob
	{
		TSP::TSPData& TSPData;
		TSP::TSPConfig& TSPConfig;

	public:
		void operator()(tbb::blocked_range<size_t> range) const
		{

			bool firstIndivdualChange = false;
			bool secoundIndivdualChange = false;
			int index = 0;

			for (size_t i = range.begin(); i != range.end(); ++i)
			{

				index = i * 2;
				if (index > TSPData.indivduals.size())
				{
					index--;
					break;
				}

				if (TSPConfig.selectionType == TSP::SelectionType::tournament)
				{
					TSPData.selection[index] = TSP::Selector::turnamentSelection(TSPConfig.tournamnetSize, TSPData.indivduals);
					TSPData.selection[index + 1] = TSP::Selector::turnamentSelection(TSPConfig.tournamnetSize, TSPData.indivduals);
				}

				//Crossover
				TSP::Crossover::crossPair(TSPConfig.copyChance, TSPData.getIndivdualBySelection(index), TSPData.getIndivdualBySelection(index + 1),
					TSPData.nextGeneration[index], TSPData.nextGeneration[index + 1]);

				switch (TSPConfig.mutationType)
				{
					case MutationType::inversion:
						TSP::Mutator::mutateInversion(TSPData.nextGeneration[index], TSPConfig.mutation);
						TSP::Mutator::mutateInversion(TSPData.nextGeneration[index + 1], TSPConfig.mutation);
						break;
					case MutationType::exchange:
						TSP::Mutator::mutateExchanage(TSPData.nextGeneration[index], TSPConfig.mutation);
						TSP::Mutator::mutateExchanage(TSPData.nextGeneration[index + 1], TSPConfig.mutation);
						break;
					default:
						TSP::Mutator::mutateInversion(TSPData.nextGeneration[index], TSPConfig.mutation);
						TSP::Mutator::mutateInversion(TSPData.nextGeneration[index + 1], TSPConfig.mutation);
						break;
				}

				//FitnessFunction
				TSP::FitnessFunction::fitnessFunction(TSPData.nextGeneration[index], TSPData.distances);
				TSP::FitnessFunction::fitnessFunction(TSPData.nextGeneration[index + 1], TSPData.distances);

				firstIndivdualChange = false;
				secoundIndivdualChange = false;
			}

			if (index >= 0 && index % 2 != 0)
			{
				TSPData.copyToNextGeneration(index);
			}
		}

		TSPJob(TSP::TSPData& TSPData,TSP::TSPConfig& TSPConfig)
			: TSPData(TSPData),TSPConfig(TSPConfig)
		{}
	};
}