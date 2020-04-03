#pragma once

#include <vector>


namespace TSP 
{
	using namespace std;

	class Selector
	{
	public:
		static void ruletSelection(vector<vector<int>>& individuals, vector<int>& selection)
		{
			int max = individuals[0].back();

			for (size_t i = 1; i < individuals.size(); i++)
			{
				if (max < individuals[i].back())
				{
					max = individuals[i].back();
				}
			}

			for (size_t i = 0; i < individuals.size(); i++)
			{
				individuals[i].back() = max + 1 - individuals[i].back();
			}

			int sumUpIndividuals = 0;

			for (size_t i = 0; i < individuals.size(); i++)
			{
				sumUpIndividuals += individuals[i].back();
			}

			for (size_t i = 0; i < individuals.size(); i++)
			{
				int randomValue = rand() % sumUpIndividuals;
				int internalSum = 0;


				for (size_t j = 0; j < individuals.size(); j++)
				{
					internalSum += individuals[j].back();
					if (internalSum > randomValue)
					{
						selection[i] = j;
						break;
					}
				}

			}
		}
		
		static void turnamentSelection(int tournamentSize, vector<vector<int>>& individuals, vector<int>& selection) 
		{
			for (size_t i = 0; i < individuals.size(); i++)
			{

				int best = rand() % individuals.size();
				int randomIndex;
				for (size_t j = 0; j < tournamentSize - 1; j++)
				{
					randomIndex = rand() % individuals.size();
					if (individuals[randomIndex].back() < individuals[best].back())
					{
						best = randomIndex;
					}
				}

				selection[i] = best;
			}
		}

	private:

	};

}