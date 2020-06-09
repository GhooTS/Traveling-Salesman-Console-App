#pragma once

#include <vector>


namespace TSP
{

	static class IndivdualsGenerator
	{
	public:
		/// <summary>
		/// Generate random indviduals
		/// </summary>
		/// <param name="numberOfIndividuals"></param>
		/// <param name="numberOfGens">size of individual</param>
		/// <param name="lastScore">is the last element of individual score from fitness function?</param>
		/// <returns></returns>
		static std::vector<std::vector<int>> generate(int numberOfIndividuals,int numberOfGens,bool lastScore) 
		{

			std::vector<std::vector<int>> output(numberOfIndividuals);

			numberOfGens = lastScore ? numberOfGens + 1 : numberOfGens;

			for (size_t i = 0; i < output.size(); i++)
			{

				output[i].reserve(numberOfGens);

				for (size_t j = 0; j < output[i].capacity() - 1; j++)
				{
					output[i].push_back(j);
				}

				for (size_t j = 0; j < output[i].size() - 1; j++)
				{
					int randNum = rand() % (output[i].size() - 1);
					int tmp = output[i][randNum];
					output[i][randNum] = output[i][j];
					output[i][j] = tmp;
				}
				if (lastScore) 
				{
					output[i].push_back(0);
				}
			}


			return output;
		}


		static void generateNewComers(std::vector<std::vector<int>> indivduals,int generateAmount) 
		{
			for (size_t i = 0; i < generateAmount; i++)
			{
				int index = rand() % (indivduals.size() - 1);

				for (size_t j = 0; j < indivduals[index].size(); j++)
				{
					int randNum = rand() % (indivduals[index].size() - 1);
					int tmp = indivduals[index][randNum];
					indivduals[index][randNum] = indivduals[index][j];
					indivduals[index][j] = tmp;
				}
			}
		}
	private:

	};

}