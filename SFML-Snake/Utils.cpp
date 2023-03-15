#include "Utils.h"
#include <regex>

// Sprawdzamy iloœæ znaków z wykorzystaniem biblioteki "regex"
bool Utils::isValidTwo(std::string text)
{
	std::regex pattern = std::regex("\\d{2}");
	return std::regex_match(text, pattern);
}

bool Utils::isValidThree(std::string text)
{
	std::regex pattern = std::regex("\\d{3}");
	return std::regex_match(text, pattern);
}

bool Utils::isValidSpeed(std::string text)
{
	std::regex pattern = std::regex(".{4,}");
	return std::regex_match(text, pattern);
}

std::string Utils::GetFormattedNumericString(const std::string& string)
{
	std::string text = string;

	// Je¿eli wiêcej ni¿ 4 znaki, mamy do czynienia z tekstem prêdkoœci
	if (isValidSpeed(text))
	{
		text = text.substr(0, 3);
	}

	// Je¿eli jednocyfrowy wynik, dodajemy dwa zera
	else if (!isValidTwo(text))
	{
		text = "00" + text;
	}

	// Je¿eli dwucyfrowy wynik, dodajemy jedno zero
	else if (!isValidThree(text))
	{
		text = "0" + text;
	}

	return text;
}