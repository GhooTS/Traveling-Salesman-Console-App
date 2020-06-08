#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace InvidualsUtiltiy 
{

    inline std::string toString(std::vector<int>& vec)
    {
        std::string output;
        for (size_t i = 0; i < vec.size() - 1; i++)
        {
            output += std::to_string(vec[i]);
            if (i != vec.size() - 2)
            {
                output += "-";
            }
        }
        output += " " + std::to_string(vec.back()) + "\n";

        return output;
    }

    inline void display(std::vector<int>& vec)
    {
        for (size_t i = 0; i < vec.size() - 1; i++)
        {
            std::cout << vec[i];
            if (i != vec.size() - 2)
            {
                std::cout << "-";
            }
        }
        std::cout << " " << vec.back() << std::endl;
    }

    inline void displayAll(std::vector<std::vector<int>>& vec)
    {
        for (size_t i = 0; i < vec.size(); i++)
        {
            display(vec[i]);
        }
    }

    inline int sumUp(std::vector<std::vector<int>>& vec)
    {
        int output = 0;

        for (size_t i = 0; i < vec.size(); i++)
        {
            output += vec[i].back();
        }

        return output;
    }

    inline int findBest(std::vector<std::vector<int>>& vec)
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

    inline int fintWorst(std::vector<std::vector<int>>& vec)
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
}