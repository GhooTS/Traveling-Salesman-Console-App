#pragma once

#include "SImpleCommandLine.h"
#include "TSPRunner.h"
#include "TSPConfig.h"
#include "TSPResult.h"
#include "Utility/MatrixGenerator.h"
#include "Utility/FileContentExtractor.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "ChangeValueCommand.h"
#include "Utility/IndividualsUtility.h"



class TSPRunCommand : public Command
{
	void execute(std::vector<std::string>& args)
	{
		try {
			if (data.isDistanceMatrixValide() == false) 
			{
				std::cout << "invalide distance matrix" << std::endl;
				return;
			}
			data.generateIndivduals(config.numberOfIndividuals);
			results.push_back(TSP::TSPRunner::run(data, config));
			results.back().printResult();
		}
		catch (exception& exp) 
		{
			std::cout << exp.what() << std::endl;
			return;
		}
	}
public:	
	TSPRunCommand(std::string name, std::string descirption,TSP::TSPData& data,TSP::TSPConfig& config, std::vector<TSP::TSPResult>& results)
		: Command(name,descirption,0), data(data),config(config),results(results)
	{
		
	}

	TSP::TSPConfig& config;
	TSP::TSPData& data;
	std::vector<TSP::TSPResult>& results;
};

class TSPSetDistanceMatrixCommand : public Command
{
	void execute(std::vector<std::string>& args)
	{
		try {
			std::vector<std::string> fileContent = Utility::getFileContent(args[0]);
			auto fileFormat = Utility::splite(args[0], ".")[1];
			if (fileFormat == "txt" || fileFormat == "tsp") {
				data.setDistanceMatrix(TSP::MatrixGenerator::generate(fileContent, fileFormat == "tsp"));
				config.from = args[0];
			}
			else 
			{
				std::cout << "file format is incorrect, only .txt and .tsp allowed" << std::endl;
			}
		}
		catch (exception& exp)
		{
			std::cout << exp.what() << std::endl;
			return;
		}

		std::cout << "distance matrix set correcly" << std::endl;
	}
public:
	TSPSetDistanceMatrixCommand(std::string name, std::string descirption, TSP::TSPData& data, TSP::TSPConfig& config)
		: Command(name, descirption, 1), data(data), config(config)
	{

	}

	TSP::TSPData& data;
	TSP::TSPConfig& config;
};

class TSPShowConfigCommand : public Command
{
	void execute(std::vector<std::string>& args)
	{
		std::cout << config.ToString() << std::endl;
	}
public:
	TSPShowConfigCommand(std::string name, std::string descirption, TSP::TSPConfig& config)
		: Command(name, descirption, 0), config(config)
	{

	}
	TSP::TSPConfig& config;
};

class TSPResultSaveCommand : public Command
{
	void execute(std::vector<std::string>& args)
	{
		if (args[0] == "all")
		{
			for (int i = 0;i < results.size();i++)
			{
				if (save(i)) {
					std::cout << "Result with ID " << i;
					std::cout << " has been save to ";
					std::cout << results[i].getResultFilePath() << std::to_string(sessionId) << ".txt" << std::endl;
				}
			}
		}
		else
		{
			try
			{
				int index = stoi(args[0]);
				if (index >= 0 && index < results.size())
				{
					if (save(index)) {
						std::cout << "Result with ID " << index;
						std::cout << " has been save to ";
						std::cout << results[index].getResultFilePath() << std::to_string(sessionId) << ".txt" << std::endl;
					}
				}
			}
			catch (std::invalid_argument& exp)
			{
				std::cout << exp.what() << std::endl;
				return;
			}
			catch (std::out_of_range& exp)
			{
				std::cout << exp.what() << std::endl;
				return;
			}
		}
	}
public:
	TSPResultSaveCommand(std::string name, std::string descirption, int sessionId, std::vector<TSP::TSPResult>& results)
		: Command(name, descirption, 1), sessionId(sessionId), results(results)
	{

	}


	int sessionId;
	std::vector<TSP::TSPResult>& results;
private:
	bool save(int index) 
	{
		if (results[index].saved) return false;

		std::ofstream resultFile(results[index].getResultFilePath() + std::to_string(sessionId) + ".txt",std::ios::app);

		resultFile << std::endl;
		resultFile << "config:" << std::endl;
		resultFile << results[index].config.ToString() << std::endl;
		resultFile << "best path: ";
		resultFile << InvidualsUtiltiy::toString(results[index].bestPath);

		resultFile.close();

		results[index].saved = true;

		return true;
	}
};

class TSPShowResult : public Command
{
	void execute(std::vector<std::string>& args)
	{
		std::cout << std::setw(3)  << std::left << "#";
		std::cout << std::setw(15) << std::left << "Path length";
		std::cout << std::setw(50) << std::left << "From file";
		std::cout << std::setw(6)  << std::left << "Saved" << std::endl;

		if (args[0] == "all") 
		{
			for (int i = 0;i < results.size();i++)
			{
				show(i);
			}

			if (results.size() == 0) 
			{
				cout << "no result to be shown" << std::endl;
			}
		}
		else 
		{
			try
			{
				int index = stoi(args[0]);
				if (index >= 0 && index < results.size())
				{
					show(index);
				}
				else 
				{
					std::cout << "result with ID " << std::to_string(index) << " doesn't exist" << std::endl;
				}
			}
			catch (std::invalid_argument& exp)
			{
				std::cout << exp.what() << std::endl;
			}
			catch (std::out_of_range& exp)
			{
				std::cout << exp.what() << std::endl;
			}
			
		}

		
	}

public:
	TSPShowResult(std::string name, std::string descirption, std::vector<TSP::TSPResult>& results)
		: Command(name, descirption, 1), results(results)
	{}

	std::vector<TSP::TSPResult>& results;
private:
	void show(int index) 
	{
		std::cout << std::setw(3)  << std::left << index;
		std::cout << std::setw(15) << std::left << results[index].bestPath.back();
		std::cout << std::setw(50) << std::left << results[index].config.from;
		std::cout << std::setw(6)  << std::left << (results[index].saved ? "Yes" : "No") << std::endl;
	}
};

template<>
class ChangeValueCommand<TSP::MutationType> : public Command
{
	void execute(std::vector<std::string>& args)
	{
		try
		{
			TSP::MutationType oldValue = value;

			int index = std::stoi(args[0]);
			if(index == 1)
				value = TSP::MutationType::inversion;
			else if(index == 2)
				value = TSP::MutationType::exchange;
			else {
				std::cout << "incorrect argument" << std::endl;
				return;
			}

			std::cout << "Change from " << TSP::MutationEnumMap.at(oldValue) << " to " << TSP::MutationEnumMap.at(value) << std::endl;
		}
		catch (std::invalid_argument& exp)
		{
			std::cout << exp.what() << std::endl;
		}
		catch (std::out_of_range& exp)
		{
			std::cout << exp.what() << std::endl;
		}
		
	}
public:
	ChangeValueCommand(std::string name, std::string descirption, TSP::MutationType& value)
		: Command(name, descirption, 1), value(value)
	{}
	TSP::MutationType& value;
};

template<>
class ChangeValueCommand<TSP::SelectionType> : public Command
{
	void execute(std::vector<std::string>& args)
	{
		
		try
		{
			TSP::SelectionType oldValue = value;

			int index = std::stoi(args[0]);

			if(index == 1)
				value = TSP::SelectionType::rulet;
			else if(index == 2)
				value = TSP::SelectionType::tournament;
			else {
				std::cout << "incorrect argument " << index << std::endl;
				return;
			}
			std::cout << "Change from " << TSP::SelectionTypeEnumMap.at(oldValue) << " to " << TSP::SelectionTypeEnumMap.at(value) << std::endl;
		}
		catch (std::invalid_argument& exp)
		{
			std::cout << exp.what() << std::endl;
		}
		catch (std::out_of_range& exp)
		{
			std::cout << exp.what() << std::endl;
		}
	}
public:
	ChangeValueCommand(std::string name, std::string descirption, TSP::SelectionType& value)
		: Command(name, descirption, 1), value(value)
	{}
	TSP::SelectionType& value;
};
