#pragma once
#include <vector>
#include <string>
#include "Utility/IndivdualsGenerator.h"
#include "Utility/IndividualsUtility.h"

namespace TSP 
{
    class TSPData
    {
    public:
        std::vector<std::vector<int>> distances;
        std::vector<int> selection; // use to store selcted indivduals
        std::vector<std::vector<int>> indivduals; //current generation
        std::vector<std::vector<int>> nextGeneration;
        std::vector<int> best; // the best indivdual in all generation 

        TSPData() 
        {
            selection = vector<int>(0);
            indivduals = vector<vector<int>>(0);
            nextGeneration = vector<vector<int>>(0);
            best = vector<int>(0);
        }
        void setDistanceMatrix(std::vector<std::vector<int>> distnaces)
        {
            this->distances = distnaces;
            distanceMatrixValide = true;
        }

        void generateIndivduals(int amount)
        {
            if (amount % 2 == 1)
            {
                amount++;
            }

            if (amount <= 0) 
            {
                amount = 2;
            }

            indivduals = TSP::IndivdualsGenerator::generate(amount, distances.size(), true);
            nextGeneration.resize(amount);
            selection.resize(amount);
            initalNextGeneration();
            best.resize(indivduals[0].size());
        }

        void SetBest() 
        {
            best = indivduals[InvidualsUtiltiy::findBest(indivduals)];
        }

        void copyToNextGeneration(int index) 
        {
            copy(indivduals[selection[index]].begin(), indivduals[selection[index]].end(), nextGeneration[index].begin());
        }

        void passGeneration() 
        {
            indivduals.swap(nextGeneration);
        }

        std::vector<int>& getIndivdualBySelection(int index) 
        {
            return indivduals[selection[index]];
        }

        bool isDistanceMatrixValide()
        {
            return distanceMatrixValide;
        }

        ~TSPData() 
        {

        }

       
    private:
        bool distanceMatrixValide;
        void initalNextGeneration()
        {
            for (size_t i = 0; i < nextGeneration.size(); i++)
            {
                nextGeneration[i].resize(indivduals[0].size());
            }
        }

    };
}