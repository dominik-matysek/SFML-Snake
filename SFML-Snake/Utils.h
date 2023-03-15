#pragma once
#include <string>
// Klasa do modyfikacji wyœwietlania wyników
class Utils
{
private:
	Utils();

public:
	// Zamiana int na string w odpowiednim formacie (3 => 003, 31 => 031)
	static std::string GetFormattedNumericString(const std::string& string);
	// Sprawdzamy czy prêdkoœæ
	static bool isValidSpeed(std::string text);
	// Sprawdzamy ile 0 dodaæ
	static bool isValidTwo(std::string text);
	static bool isValidThree(std::string text);
};