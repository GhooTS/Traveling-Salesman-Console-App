#pragma once

#include <string>
#include <iostream>

template<class T>
inline T convertToPrimitive(std::string value) 
{
	throw std::exception("incompatiable type");
}

template<>
int convertToPrimitive<int>(std::string value)
{
	return std::stoi(value);
}

template<>
double convertToPrimitive<double>(std::string value)
{
	return std::stod(value);
}

template<>
float convertToPrimitive<float>(std::string value)
{
	return std::stof(value);
}

template<>
long convertToPrimitive<long>(std::string value)
{
	return std::stol(value);
}

template<>
long double convertToPrimitive<long double>(std::string value)
{
	return std::stold(value);
}

template<>
long long convertToPrimitive<long long>(std::string value)
{
	return std::stoll(value);
}

template<>
unsigned long convertToPrimitive<unsigned long>(std::string value)
{
	return std::stoul(value);
}

template<>
unsigned long long convertToPrimitive<unsigned long long>(std::string value)
{
	return std::stoull(value);
}