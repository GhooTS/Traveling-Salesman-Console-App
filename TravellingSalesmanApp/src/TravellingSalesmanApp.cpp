
// TravellingSalesmanApp.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "TSP.h"
#include "Utility/FileContentExtractor.h"
#include <vector>
#include <chrono>
#include "Utility/IndividualsUtility.h"
#include "SImpleCommandLine.h"
#include "Commands/ChangeValueCommand.h"
#include "Commands/TSPCommands.h"



int main()
{
    //Get new seed
    srand(time(NULL));
    TSP::TSPConfig config;
    TSP::TSPData data;
    std::vector<TSP::TSPResult> results;
    SimpleCommandReader commandReader;
    bool run = true;

    int sessionID = rand(); //use to name result file

    commandReader.AddCommand(new TSPRunCommand("start","start TSPRunner with current config",data,config,results));
    commandReader.AddCommand(new ChangeValueCommand<bool>("exit","exit appliaction",run,nullptr,false));
    

    commandReader.AddCommand(new TSPSetDistanceMatrixCommand("DM","sets distance matrix",data,config));
    commandReader.AddCommand(new ChangeValueCommand<int>("DI","set how often information about current generation is show",config.displayInterval,0, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("NOI","set number of individuals",config.numberOfIndividuals, 0, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("NOG","set number of generation",config.numberOfGeneration, 1, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("TSize","set tournament size",config.tournamnetSize, 2, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<TSP::SelectionType>("ST","set selection type 1 = rulet 2 = tournament ",config.selectionType));
    commandReader.AddCommand(new ChangeValueCommand<double>("CC","set copy change from 0 (0%) to 1 (100%)",config.copyChance,0,1));
    commandReader.AddCommand(new ChangeValueCommand<double>("MC","set mutation change from 0 (0%) to 1 (100%)",config.mutation,0,1));
    commandReader.AddCommand(new ChangeValueCommand<TSP::MutationType>("MT","set mutation type 1 = inversion 2 = exchange ",config.mutationType));
    
    commandReader.AddCommand(new TSPShowConfigCommand("showConfig","display current config",config));
    commandReader.AddCommand(new TSPShowResult("showResults","display results type all to see all or index to see to see one of resluts",results));
    commandReader.AddCommand(new TSPResultSaveCommand("saveResult","save results type all to see all or index to see to see one of resluts",sessionID,results));
   

    std::cout << "Copyright (c) 2020 Krzysztof Biernat\n\n";

    while (run)
    {
        std::cout << "> ";
        commandReader.ReadCommand();
    }
    commandReader.~SimpleCommandReader();
}