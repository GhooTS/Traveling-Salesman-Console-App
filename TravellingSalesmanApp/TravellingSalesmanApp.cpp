
// TravellingSalesmanApp.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <tbb\tbb.h>
#include "TSP.h"
#include "FileContentExtractor.h"
#include <vector>
#include <chrono>


void display(std::vector<int>& vec) 
{
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        cout << vec[i];
        if (i != vec.size() - 2) 
        {
            cout << "-";
        }
    }
    cout << " " << vec.back() << endl;
}

void displayAll(std::vector<std::vector<int>>& vec) 
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        display(vec[i]);
    }
}

int sumUp(std::vector<std::vector<int>>& vec) 
{
    int output = 0;

    for (size_t i = 0; i < vec.size(); i++)
    {
        output += vec[i].back();
    }

    return output;
}

int findBest(std::vector<std::vector<int>>& vec) 
{
    int bestIndex = 0;

    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[bestIndex].back() > vec[i].back()) 
        {
            bestIndex = i;
        }
    }

    return bestIndex;
}

int fintWorst(std::vector<std::vector<int>>& vec) 
{
    int output = 0;

    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[output].back() < vec[i].back())
        {
            output = i;
        }
    }

    return output;
}

int GetIntFromUser(std::string question,std::string invalideArgExp = "incorrect number",std::string outOfRangeExp = "number is too larg or too small")
{
    std::string answer;
    int output = 0;
    bool correctAnswer;
    do
    {
        correctAnswer = true;
        std::cout << question;
        std::cin >> answer;
        try {
            output = std::stoi(answer);
        }
        catch (std::invalid_argument e)
        {
            std::cout << invalideArgExp << std::endl;
            correctAnswer = false;
        }
        catch (std::out_of_range e)
        {
            std::cout << outOfRangeExp << std::endl;
            correctAnswer = false;
        }

    } while (correctAnswer == false);

    return output;
}

float GetFloatFromUser(std::string question, std::string invalideArgExp = "incorrect number", std::string outOfRangeExp = "number is too larg or too small")
{
    std::string answer;
    float output;
    bool correctAnswer;
    do
    {
        correctAnswer = true;
        std::cout << question;
        std::cin >> answer;
        try {
            output = std::stof(answer);
        }
        catch (std::invalid_argument e)
        {
            std::cout << invalideArgExp << std::endl;
            correctAnswer = false;
        }
        catch (std::out_of_range e)
        {
            std::cout << outOfRangeExp << std::endl;
            correctAnswer = false;
        }

    } while (correctAnswer == false);

    return output;
}

int GetIntInRange(std::string question, int min, int max, std::string notInRangeExp = "not in range")
{
    float output;
    bool inRange;
    do
    {
        inRange = true;
        output = GetIntFromUser(question);
        if (output < min || output > max)
        {
            std::cout << notInRangeExp << std::endl;
            inRange = false;
        }
    } while (inRange == false);

    return output;
}

float GetFloatInRange(std::string question,float min,float max,std::string notInRangeExp = "not in range") 
{
    float output;
    bool inRange;
    do 
    {
        inRange = true;
        output = GetFloatFromUser(question);
        if (output < min || output > max) 
        {
            std::cout << notInRangeExp << std::endl;
            inRange = false;
        }
    } while (inRange == false);

    return output;
}


bool UserConfirmation(std::string question,std::string confirm = "y",std::string cancel = "n") 
{
    std::string answer;


    do 
    {
        std::cout << question << "? ";
        std::cin >> answer;
        if (answer == confirm) 
        {
            return true;
        }
        else if (answer == cancel) 
        {
            return false;
        }
        else 
        {
            std::cout << "type " << confirm << " or " << cancel << endl;
        }

    } while (true);
}

int main()
{
    int numberOfIndividuals = 100,numberOfGens = 0;
    double mutation = 0.05;
    double copyChance = 0.05;
    int tournamnetSize = 10;
    int numberOfGeneration = 10000;
    int displayInterval = 100;
    int bestGetBestAtGeneration = 0;
    std::string fileName = "berlin52";
    std::string filePath = "G:\\TSP";
    std::string command = "";
    bool resetValue = true;

    

    TSP::Selector selector = TSP::Selector();
    std::vector<std::string> fileContent;

    do {
        //Get new seed
        srand(time(NULL));

        auto start = chrono::steady_clock::now();
        auto end = chrono::steady_clock::now();
        auto diff = end - start;


    #pragma region TSP USER CONFIG
        //User options
        if (resetValue)
        {
            resetValue = false;
            //Get file Name
           
            bool correctAnswer;
            do {

                correctAnswer = true;
                if (UserConfirmation("change file path (current: " + filePath + " )")) {
                    std::cout << "file path: " << std::endl;
                    std::cin >> filePath;
                }
                if (UserConfirmation("change file name (current: " + fileName + " )"))
                {
                    std::cout << "file name: " << std::endl;
                    std::cin >> fileName;
                }

                fileContent = Utility::getFileContent(filePath + "\\" + fileName + ".txt");

                if (fileContent.size() == 0)
                {
                    std::cout << "file is empty or not found" << std::endl;
                    correctAnswer = false;
                }
            } while (correctAnswer == false);
            
            //Get number of generation
            if (UserConfirmation("change number of generation (current: " + std::to_string(numberOfGeneration) + " )")) {
                numberOfGeneration = GetIntInRange("number of generation: ", 0, 10000000);
            }
            //Get number of indivduals
            if (UserConfirmation("change number of indivduals (current: " + std::to_string(numberOfIndividuals) + " )")) {
                do {
                    numberOfIndividuals = GetIntInRange("number of indivduals: ", 0, 10000000);
                    if (numberOfIndividuals % 2 != 0)
                    {
                        std::cout << "only odd number of indivduals allowed" << std::endl;
                    }
                } while (numberOfIndividuals % 2 != 0);
            }
            //Get tournament size 
            if (UserConfirmation("change tournament size (current: " + std::to_string(tournamnetSize) + " )")) {
                tournamnetSize = GetIntInRange("tournament size(selection): ", 0, 10000000);
            }
            //Get mutation chance
            if (UserConfirmation("change mutation (current: " + std::to_string(mutation) + " )")) {
                mutation = (double)GetFloatInRange("mutation chance(0,1): ", 0.0f, 1.0f);
            }
            //Get copy chance
            if (UserConfirmation("change copy chance (current: " + std::to_string(copyChance) + " )")) {
                copyChance = (double)GetFloatInRange("copy chance(0,1): ", 0.0f, 1.0f);
            }
            if (UserConfirmation("change display interval (current: " + std::to_string(displayInterval) + " )")) 
            {
                displayInterval = GetIntInRange("display interval: ",0,100000000);
            }
        }
        else
        {
            fileContent = Utility::getFileContent(filePath + "\\" + fileName + ".txt");
        }
    #pragma endregion
        
    #pragma region TSP DATA
        std::vector<std::vector<int>> distances = TSP::MatrixGenerator::genrate(fileContent, true);
        std::vector<int> selection(numberOfIndividuals);
        fileContent.~vector();
        numberOfGens = distances.size();
        std::vector<std::vector<int>> indivduals = TSP::IndivdualsGenerator::generate(numberOfIndividuals, numberOfGens, true);
        std::vector<std::vector<int>> nextGeneration(numberOfIndividuals);
        std::vector<int> best(distances.size() + 1);


        for (size_t i = 0; i < nextGeneration.size(); i++)
        {
            nextGeneration[i] = std::vector<int>(indivduals[i].size());
        }

        

        for (size_t i = 0; i < indivduals.size(); i++)
        {
            TSP::FitnessFunction::fitnessFunction(indivduals[i], distances);
        }

        best = indivduals[findBest(indivduals)];
    #pragma endregion

    #pragma region TSP RUNNER
        for (size_t i = 0; i < numberOfGeneration; i++)
        {

            selector.turnamentSelection(tournamnetSize, indivduals, selection);
            //selector.ruletSelection(indivduals, selection);


            start = chrono::steady_clock::now();
            tbb::parallel_for(tbb::blocked_range<size_t>(0, indivduals.size() / 2),
                TSP::TSPJob(copyChance, mutation, indivduals, nextGeneration, distances, selection));
            end = chrono::steady_clock::now();
            diff += end - start;

            indivduals.swap(nextGeneration);
            int bestLocal = findBest(indivduals);
            if (best.back() > indivduals[bestLocal].back())
            {
                best = indivduals[bestLocal];
                bestGetBestAtGeneration = i;
            }

            if (i % displayInterval == 0)
            {
                std::cout << "best: " << best.back() << endl;
                std::cout << "get best at generation: " << bestGetBestAtGeneration << endl;
                std::cout << "best local: " << indivduals[bestLocal].back() << endl;
                std::cout << "worst local: " << indivduals[fintWorst(indivduals)].back() << endl;
                std::cout << "avg: " << sumUp(indivduals) / indivduals.size() << endl;
                std::cout << "generation: " << i << endl;
            }

        }
    #pragma endregion

    #pragma region TSP RESULT
        std::cout << std::endl << "result : ";
        display(best);
        std::cout << std::endl << "from file: " << filePath << std::endl << std::endl;
        std::cout << "config:" << std::endl;
        std::cout << "number of generation: " << numberOfGeneration << std::endl;
        std::cout << "number of individuals: " << numberOfIndividuals << std::endl;
        std::cout << "tournament size: " << tournamnetSize << std::endl;
        std::cout << "mutation: " << mutation << std::endl;
        std::cout << "copy chance: " << copyChance << std::endl;
        std::cout << std::endl << std::endl;
        std::cout << "execution time: " << chrono::duration<double, milli>(diff).count() << "ms" << std::endl << std::endl;
    #pragma endregion  

    #pragma region User OPTIONS
        
        if (UserConfirmation("write result to file?"))
        {

            std::ofstream out;
            out.open(filePath + "\\" + fileName + " result.txt", std::ios::app);
            
            
            out << std::endl << "from file: " << fileName << std::endl << std::endl;
            out << "config:" << std::endl;
            out << "number of generation: " << numberOfGeneration << std::endl;
            out << "number of individuals: " << numberOfIndividuals << std::endl;
            out << "tournament size: " << tournamnetSize << std::endl;
            out << "mutation: " << mutation << std::endl;
            out << "copy chance: " << copyChance << std::endl;
            out << "best at generation: " << bestGetBestAtGeneration << std::endl;
            out << std::endl;
            out << "execution time: " << chrono::duration<double, milli>(diff).count() << "ms" << std::endl;
            out << "Path: ";
            for (size_t i = 0; i < best.size() - 1; i++)
            {
                out << best[i];

                if (i != best.size() - 2)
                {
                    out << "-";
                }
            }
            out << " " << best.back();
            out << std::endl << std::endl;

            out.close();
        }



        std::cout << "'r' to restart" << std::endl;
        std::cout << "'rs' to restart and change options" << std::endl;
        std::cout << "type any thing to exit" << std::endl;
        cin >> command;
        if (command == "rs")
        {
            resetValue = true;
            command = "r";
        }
    #pragma endregion

        
        
    } while (command == "r");

}