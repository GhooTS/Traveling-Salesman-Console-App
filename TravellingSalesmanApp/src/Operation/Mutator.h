#pragma once

#include <vector>

namespace TSP 
{
	using namespace std;

	class Mutator
	{
	public:
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
		static void potatoMutation(std::vector<std::vector<int>>& individuals, double mutationChance)
		{

			for (size_t i = 0; i < individuals.size(); i++)
			{
				double randomNum = (double)rand() / RAND_MAX;
				if (randomNum < mutationChance)
				{
					int randomIndex = rand() % (individuals[i].size() - 2);
					int tmp = individuals[i][randomIndex];

					if (rand() % 100 < 51)
					{
						int next = randomIndex + 1;
						next = next < individuals[i].size() - 1 ? next : 0;
						individuals[i][randomIndex] = individuals[i][next];
						individuals[i][next] = tmp;
					}
					else
					{
						int prev = randomIndex - 1;
						prev = prev >= 0 ? prev : individuals[i].size() - 2;
						individuals[i][randomIndex] = individuals[i][prev];
						individuals[i][prev] = tmp;
					}
				}
			}
		}

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
		static void potatoMutation(vector<int>& individuals, double mutationChance)
		{

			double randomNum = (double)rand() / RAND_MAX;
			if (randomNum < mutationChance)
			{
				int randomIndex = rand() % (individuals.size() - 2);
				int tmp = individuals[randomIndex];

				if (rand() % 100 < 51)
				{
					int next = randomIndex + 1;
					next = next < individuals.size() - 3 ? next : 0;
					individuals[randomIndex] = individuals[next];
					individuals[next] = tmp;
				}
				else
				{
					int prev = randomIndex - 1;
					prev = prev >= 0 ? prev : individuals.size() - 3;
					individuals[randomIndex] = individuals[prev];
					individuals[prev] = tmp;
				}
			}
		}
		private:
			Mutator() {};
	};
}