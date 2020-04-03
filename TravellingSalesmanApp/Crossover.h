#pragma once

#include <vector>
#include <tbb\tbb.h>


namespace TSP 
{

	class Crossover
	{
	public:
		static void crossPair(double copyChance,const std::vector<int>& parentOne, const std::vector<int>& parentTwo, std::vector<int>& childOne, std::vector<int>& childTwo)
		{

			int maxIndex = parentOne.size() - 1;

			double avg = (parentOne.back() + parentTwo.back()) / 2;
			int min = fmin(parentOne.back(), parentTwo.back());
			double levelOfSomething = 1 - (double)(min / avg);

			double randomNum = (double)rand() / RAND_MAX;
			if (randomNum < copyChance + levelOfSomething)
			{
				copy(parentOne.begin(), parentOne.end(), childOne.begin());
				copy(parentTwo.begin(), parentTwo.end(), childTwo.begin());
			}
			else {
				int startIndex = rand() % (maxIndex - 1);
				int endIndex = rand() % (maxIndex - startIndex) + startIndex;

				if (endIndex == maxIndex) {
					std::cout << "max" << std::endl;
				}

				for (size_t j = startIndex; j < endIndex; j++)
				{
					childOne[j] = parentTwo[j];
					childTwo[j] = parentOne[j];
				}

				exchangeGens(parentOne, childOne, startIndex, endIndex);
				exchangeGens(parentTwo, childTwo, startIndex, endIndex);
			}

		}

		static int containe(int value, std::vector<int>& children, int from, int to)
		{

			for (size_t i = from; i < to; i++)
			{
				if (value == children[i])
				{
					return i;
				}
			}

			return -1;
		}

		static void exchangeGens(const std::vector<int>& parent, std::vector<int>& child, int from, int to)
		{
			for (size_t i = 0; i < from; i++)
			{
				int value = parent[i];
				int index;
				while ((index = containe(value, child, from, to)) != -1)
				{
					value = parent[index];
				}
				child[i] = value;
			}

			for (size_t i = to; i < child.size() - 1; i++)
			{
				int value = parent[i];
				int index;
				while ((index = containe(value, child, from, to)) != -1)
				{
					value = parent[index];
				}
				child[i] = value;
			}
		}
	};
}