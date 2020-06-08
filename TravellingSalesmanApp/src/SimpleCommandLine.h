#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Commands/Command.h"
#include "Utility/StringToPrimitiveTypeConverter.h"
#include "Utility/StringUtility.h"

class SimpleCommandReader
{
public:
	std::vector<Command*> commands;
	void AddCommand(Command* command) 
	{
		commands.push_back(command);
	}
	void ReadCommand() 
	{
		string commandToParse;
		std::getline(std::cin, commandToParse);
		std::vector<std::string> tmp = Utility::splite(commandToParse, " ");

		if (tmp.size() == 0) 
		{
			showHint();
			return;
		}

		for (size_t i = 0; i < tmp.front().size(); i++)
		{
			tmp.front()[i] = std::toupper(tmp.front()[i]);
		}

		if (tmp.front() == "HELP" && tmp.size() == 1) 
		{
			showHelp();
			return;
		}

		if (tmp.front() == "CLEAR" && tmp.size() == 1) 
		{
			std::system("cls");
			return;
		}

		int commandIndex = FindCommand(tmp.front(), tmp.size() - 1);

		if (commandIndex != -1) 
		{
			tmp.erase(tmp.begin());
			commands[commandIndex]->execute(tmp);
		}
		else 
		{
			std::cout << "command " << tmp.front() <<" is incorect" << std::endl;
			showHint();
		}
		std::cout << std::endl;
	}


	~SimpleCommandReader() 
	{
		for (auto command : commands) 
		{
			delete command;
		}
	}
private:
	int FindCommand(std::string& name,int numberOfArgs) 
	{
		for (size_t i = 0; i < commands.size(); i++)
		{
			if (numberOfArgs == commands[i]->numberOfArgs && commands[i]->name == name) 
			{
				return i;
			}
		}

		return -1;
	}

	void showHelp() 
	{
		for (auto command : commands) 
		{
			std::cout << std::setw(25) << std::left << command->name;
			std::cout << command->description << std::endl;
		}
		std::cout << setw(25) << left << "CLEAR" << "CLEARS CONSOLE" << std::endl;
	}

	void showHint() 
	{
		std::cout << "type 'help' to see all commands" << std::endl;
	}
};
