#pragma once

#include <vector>

namespace TSP 
{
	using namespace std;

	class Mutator
	{
	public:

		//for all population
		static void mutateInversion(std::vector<std::vector<int>>& indviduals, double mutationChance)
		{
			int maxIndex = indviduals[0].size() - 1;

			for (size_t i = 0; i < indviduals.size(); i++)
			{
				double randomNum = (double)rand() / RAND_MAX;
				if (randomNum < mutationChance)
				{
					int startIndex = rand() % (maxIndex - 2);
					int endIndex = rand() % (maxIndex - startIndex - 1) + startIndex;


					int halfSize = startIndex + (endIndex - startIndex) / 2;

					for (size_t j = startIndex; j <= halfSize; j++)
					{
						int tmp = indviduals[i][j];
						indviduals[i][j] = indviduals[i][halfSize - j];
						indviduals[i][halfSize - j] = tmp;
					}
				}
			}
		}
		static void mutateExchanage(std::vector<std::vector<int>>& indviduals, double mutationChange)
		{
			for (size_t i = 0; i < indviduals.size(); i++)
			{
				double randomNum = (double)rand() / RAND_MAX;

				if (mutationChange < randomNum)
				{
					int randomIndexOne = rand() % (indviduals[i].size() - 1);
					int randomIndexTwo = rand() % (indviduals[i].size() - 1);

					if (randomIndexOne == randomIndexTwo)
					{
						randomIndexOne += randomIndexOne == 0 ? 1 : -1;
					}

					int tmp = indviduals[i][randomIndexOne];
					indviduals[i][randomIndexOne] = indviduals[i][randomIndexTwo];
					indviduals[i][randomIndexTwo] = tmp;
				}
			}
		}

		//for single indivdual
		static void mutateInversion(vector<int>& indviduals, double mutationChance)
		{
			int maxIndex = indviduals.size() - 1;

			double randomNum = (double)rand() / RAND_MAX;
			if (randomNum > mutationChance)
			{
				int startIndex = rand() % (maxIndex - 1);
				int endIndex = rand() % (maxIndex - startIndex) + startIndex;

				if (endIndex == maxIndex) 
				{
					std::cout << "max" << std::endl;
				}


				for (size_t j = 0; j <= (endIndex - startIndex) / 2; j++)
				{
					int tmp = indviduals[startIndex + j];
					indviduals[startIndex + j] = indviduals[endIndex - j];
					indviduals[endIndex - j] = tmp;
				}
			}
		}

		static void mutateInversion(vector<int>* indviduals, double mutationChance)
		{
			int maxIndex = indviduals->size() - 1;

			double randomNum = (double)rand() / RAND_MAX;
			if (randomNum > mutationChance)
			{
				int startIndex = rand() % (maxIndex - 1);
				int endIndex = rand() % (maxIndex - startIndex) + startIndex;

				if (endIndex == maxIndex)
				{
					std::cout << "max" << std::endl;
				}


				for (size_t j = 0; j <= (endIndex - startIndex) / 2; j++)
				{
					int tmp = indviduals->at(startIndex + j);
					indviduals->at(startIndex + j) = indviduals->at(endIndex - j);
					indviduals->at(endIndex - j) = tmp;
				}
			}
		}

		static void mutateExchanage(vector<int>& indviduals, double mutationChange)
		{
			double randomNum = (double)rand() / RAND_MAX;
			if (mutationChange > randomNum)
			{
				int randomIndexOne = rand() % (indviduals.size() - 1);
				int randomIndexTwo = rand() % (indviduals.size() - 1);

				if (randomIndexOne == randomIndexTwo)
				{
					randomIndexOne += randomIndexOne == 0 ? 1 : -1;
				}

				int tmp = indviduals[randomIndexOne];
				indviduals[randomIndexOne] = indviduals[randomIndexTwo];
				indviduals[randomIndexTwo] = tmp;
			}
		}
		private:
			Mutator() {};
	};
}