#pragma once

#include "SImpleCommandLine.h"
#include <string>

template<class T>
class ChangeValueCommand : public Command
{
	void execute(std::vector<std::string>& args)
	{
		T oldValue = value;
		try
		{
			value = convertToPrimitive<T>(args[0]);

			if (value < minValue || value > maxValue) 
			{
				value = oldValue;
				std::cout << "specify value must be in range (" << minValue << ", " << maxValue << ")";
				return;
			}

			std::cout << "Change from " << std::to_string(oldValue) << " to " << std::to_string(value) << std::endl;
		}
		catch (std::invalid_argument& exp)
		{
			std::cout << exp.what() << std::endl;
		}
		catch (std::out_of_range& exp)
		{
			std::cout << exp.what() << std::endl;
		}
	}
public:
	ChangeValueCommand(std::string name, std::string descirption, T& value,T minValue,T maxValue)
		: Command(name, descirption, 1), value(value), minValue(minValue), maxValue(maxValue)
	{}
	T& value;
	T minValue;
	T maxValue;
};

template<>
class ChangeValueCommand<bool> : public Command
{
	void execute(std::vector<std::string>& args)
	{
		if (numberOfArgs == 0) 
		{
			value = defaultValue;
			return;
		}

		if (valueParser == nullptr) 
		{
			throw std::runtime_error("missing parser");
		}

		if (valueParser->find(args[0]) != valueParser->end()) 
		{
			bool oldValue = value;
			value = valueParser->at(args[0]);
			std::cout << "Change from " << std::to_string(oldValue) << " to " << args.front() << std::endl;
		}

	}
public:
	ChangeValueCommand(std::string name, std::string descirption, bool& value, const std::map<std::string, bool>* valueParser, bool hasArgument = true, bool defualtValue = false)
		: Command(name, descirption, hasArgument ? 1 : 0), valueParser(valueParser),value(value),defaultValue(defualtValue)
	{
		
	}
	bool& value;
	
	
private:
	bool defaultValue;
	const std::map<std::string, bool>* valueParser;
};

template<>
class ChangeValueCommand<std::string> : public Command
{
	void execute(std::vector<std::string>& args)
	{
		std::string oldValue = value;
		
		value = args[0];

		std::cout << "Change from " << oldValue << " to " << args.front() << std::endl;
	}
public:
	ChangeValueCommand(std::string name, std::string descirption, std::string& value)
		: Command(name, descirption,1), value(value)
	{}
	std::string& value;
};


template<class T>
class SaveToFileCommand : public Command
{

};