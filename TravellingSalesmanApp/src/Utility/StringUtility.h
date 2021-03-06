#pragma once


#include <string>
#include <vector>

using namespace std;


namespace Utility 
{
	inline string& trim(string& str, const string& chars)
	{

		//str.erase(str.find_first_not_of(chars));
		str.erase(str.find_last_not_of(chars) + 1);

		return str;
	}

	inline vector<string> splite(string str, string expresion)
	{
		vector<string> output(0);

		size_t currentPosition = 0;
		size_t to;

		if (str.size() == 0) 
		{
			return output;
		}

		while ((to = str.find(expresion, currentPosition)) != string::npos) {
			output.push_back(str.substr(currentPosition, to - currentPosition));
			currentPosition = to + 1;
		}

		if (currentPosition < str.size()) 
		{
			output.push_back(str.substr(currentPosition,str.size() - currentPosition));
		}

		return output;
	}

	inline void toUpperCase(std::string& str) 
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			str[i] = std::toupper(str[i]);
		}
	}
}