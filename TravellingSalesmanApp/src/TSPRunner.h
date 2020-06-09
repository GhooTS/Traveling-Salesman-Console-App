#pragma once

#include "TSPResult.h"
#include "TSPConfig.h"
#include "TSPData.h"
#include "TSPJob.h"
#include "Operation/Selection.h"
#include <tbb/tbb.h>
#include <chrono>
#include <iomanip>
#include <math.h>


namespace TSP 
{

	class TSPRunner
	{
    public:
		static TSP::TSPResult run(TSP::TSPData& data, TSP::TSPConfig& config) 
		{
            
            data.best.back() = INT32_MAX;

            auto startTime = chrono::high_resolution_clock::now();
            for (size_t i = 0; i < config.numberOfGeneration; i++)
            {

                //tournament selection can be do in parallel in contrast to rule selection, at least in current implmentation
                switch (config.selectionType)
                {
                    case SelectionType::rulet:
                        TSP::Selector::rouletteSelection(data.indivduals, data.selection);
                        break;
                    //case SelectionType::tournament:
                    //    TSP::Selector::turnamentSelection(config.tournamnetSize, data.indivduals, data.selection);
                    //    break;
                    //default:
                    //    TSP::Selector::turnamentSelection(config.tournamnetSize, data.indivduals, data.selection);
                    //    break;
                }

                tbb::parallel_for(tbb::blocked_range<size_t>(0, data.indivduals.size() / 2),
                    TSP::TSPJob(data, config));

                data.passGeneration();
                
                int bestLocal = InvidualsUtiltiy::findBest(data.indivduals);
                if (data.best.back() > data.indivduals[bestLocal].back())
                {
                    data.best = data.indivduals[bestLocal];
                }

                if (i % config.displayInterval == 0)
                {
                    std::cout << "best: " << data.best.back() << endl;
                    std::cout << "best local: " << data.indivduals[bestLocal].back() << endl;
                    std::cout << "worst local: " << data.indivduals[InvidualsUtiltiy::fintWorst(data.indivduals)].back() << endl;
                    std::cout << "avg: " << InvidualsUtiltiy::sumUp(data.indivduals) / data.indivduals.size() << endl;
                    std::cout << "generation: " << i << endl;
                }

            }

            auto endTime = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "Execution time: " << duration.count() / (long double)1000<< " s" << std::endl;
            std::cout << "----------------------------------------------" << std::endl;

            return TSPResult(config, data.best);
		}
	};

}