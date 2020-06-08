#pragma once

#include "..\Utility\StringUtility.h"

/// <summary>
/// Base class for all commands
/// </summary>
class Command
{
public:
	Command()
	{
		this->name = "not specify";
		this->description = "not specify";
		this->numberOfArgs = 0;
	}
	Command(std::string name, std::string description, int numberOfArgs)
		: name(name),description(description), numberOfArgs(numberOfArgs)
	{
		Utility::toUpperCase(this->name);
		Utility::toUpperCase(this->description);

	}
	std::string name;
	std::string description;
	int numberOfArgs = 0;
	virtual void execute(std::vector<std::string>& args) = 0;
	virtual ~Command() {}
};