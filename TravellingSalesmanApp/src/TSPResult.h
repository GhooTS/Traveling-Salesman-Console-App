#pragma once

#include <vector>
#include <string>
#include "Utility/StringUtility.h"

namespace TSP
{

	class TSPResult
	{
	public:
		TSPResult(TSP::TSPConfig config,std::vector<int> bestPath)
			: config(config),bestPath(bestPath)
		{
		
		}

		bool saved = false;
		TSP::TSPConfig config;
		std::vector<int> bestPath;
		void printResult() 
		{
			std::cout << std::endl << "best path length: " << bestPath.back() << std::endl;
			std::cout << "with config" << std::endl;
			std::cout << config.ToString() << std::endl;
		}

		std::string getResultFilePath() 
		{
			return Utility::splite(config.from, ".")[0] + "_Result";
		}
	};
}