#pragma once

#include <tbb\tbb.h>
#include <vector>

using namespace std;


namespace TSP
{
	class TournamentSelectionJob
	{
		int tournamentSize;
		vector<vector<int>>* indiv;
		vector<int>* selection;

		public:
			void operator()(const tbb::blocked_range<size_t> range) const 
			{
				for (size_t i = range.begin(); i != range.end(); ++i)
				{
					int best = rand() % indiv->size();
					int randomIndex;
					for (size_t j = 0; j < tournamentSize - 1 ; j++)
					{
						randomIndex = rand() % indiv->size();
						if (indiv->at(randomIndex).back() < indiv->at(best).back())
						{
							best = randomIndex;
						}
					}
					selection->at(i) = best;
				}
			}
			TournamentSelectionJob(int tournamentSize, vector<vector<int>>* individuals, vector<int>* selection)
				:tournamentSize(tournamentSize), indiv(individuals), selection(selection)
			{}
	};
}