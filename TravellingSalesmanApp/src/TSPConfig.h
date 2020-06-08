#pragma once

#include <string>
#include <map>

namespace TSP
{

    enum class SelectionType
    {
        rulet, tournament
    };

    static const std::map<SelectionType, std::string> SelectionTypeEnumMap =
    {
        {SelectionType::rulet,"rulet" },
        {SelectionType::tournament,"tournament" }
    };

    enum class MutationType
    {
        inversion, exchange
    };

    static const std::map<MutationType, std::string> MutationEnumMap =
    {
        {MutationType::inversion,"inversion" },
        {MutationType::exchange,"exchange" }
    };


    class TSPConfig
    {
    public:
        int numberOfIndividuals = 100;
        double mutation = 0.05;
        double copyChance = 0.05;
        int tournamnetSize = 10;
        int numberOfGeneration = 10000;
        int displayInterval = 100;
        SelectionType selectionType = SelectionType::tournament;
        MutationType mutationType = MutationType::inversion;
        std::string from;

        std::string ToString()
        {
            std::string output = "";

            output += "number of indivduals: " + std::to_string(this->numberOfIndividuals) + "\n";
            output += "number of generation: " + std::to_string(this->numberOfGeneration) + "\n";
            output += "display interval: " + std::to_string(this->displayInterval) + "\n";
            output += "mutation chance: " + std::to_string(this->mutation) + "\n";
            output += "mutation type: " + MutationEnumMap.at(this->mutationType) + "\n";
            output += "copy chance: " + std::to_string(this->copyChance) + "\n";
            output += "selection type: " + SelectionTypeEnumMap.at(this->selectionType) + "\n";
            if (this->selectionType == SelectionType::tournament) {
                output += "tournament size: " + std::to_string(this->tournamnetSize) + "\n";
            }
            output += "from: " + from + "\n";

            return output;
        }
    };
}