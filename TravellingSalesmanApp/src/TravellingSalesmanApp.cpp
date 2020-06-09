
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
    int sessionID = rand(); //used for naming result file

    commandReader.AddCommand(new TSPRunCommand("start","start algorithm with current config",data,config,results));
    commandReader.AddCommand(new ChangeValueCommand<bool>("exit","exit appliaction",run,nullptr,false));
    

    commandReader.AddCommand(new TSPSetDistanceMatrixCommand("DM","sets distance matrix from file. Full path need to be specified to file, read readme to find out more about file format (example : DM G:/TSP/berlin52.txt)",data,config));
    commandReader.AddCommand(new ChangeValueCommand<int>("DI","sets how often information about current generation is shown",config.displayInterval,0, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("NOI","sets number of individuals",config.numberOfIndividuals, 2, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("NOG","sets number of generation",config.numberOfGeneration, 1, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<int>("TSize","sets tournament size",config.tournamnetSize, 2, INT32_MAX));
    commandReader.AddCommand(new ChangeValueCommand<TSP::SelectionType>("ST","set selection type 1 = rulet 2 = tournament ",config.selectionType));
    commandReader.AddCommand(new ChangeValueCommand<double>("CC","sets copy chance from 0 (0%) to 1 (100%)",config.copyChance,0,1));
    commandReader.AddCommand(new ChangeValueCommand<double>("MC","sets mutation chance from 0 (0%) to 1 (100%)",config.mutation,0,1));
    commandReader.AddCommand(new ChangeValueCommand<TSP::MutationType>("MT","set mutation type 1 = inversion 2 = exchange ",config.mutationType));
    
    commandReader.AddCommand(new TSPShowConfigCommand("showConfig","display current config",config));
    commandReader.AddCommand(new TSPShowResult("showResults","display results type 'all' to see all results or index to display only one",results));
    commandReader.AddCommand(new TSPResultSaveCommand("saveResult","save results type 'all' to save all results or index to save only one",sessionID,results));
   

    std::cout << "Copyright (c) 2020 Krzysztof Biernat\n\n";
    std::cout << "Hello, this is console application to find optimal solution for traveling salesman problem,\n";
    std::cout << "in order to solve any TS problem,you need to specified path to the file with distances between cites by DM command,\n";
    std::cout << "after that you can either change defualt configuration or use start command to run the algorithm.\n";
    std::cout << "Be aware that this program uses all of you cpu resoruce to decreast time needed to find optimal solution.\n";
    std::cout << "If u feal lost type 'help' to show available commands or read readme for more detailed information \n\n\n";


    while (run)
    {
        std::cout << "> ";
        commandReader.ReadCommand();
    }
    commandReader.~SimpleCommandReader();
}