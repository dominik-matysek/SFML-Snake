#pragma once
#include <string>
// Klasa do modyfikacji wy�wietlania wynik�w
class Utils
{
private:
	Utils();

public:
	// Zamiana int na string w odpowiednim formacie (3 => 003, 31 => 031)
	static std::string GetFormattedNumericString(const std::string& string);
	// Sprawdzamy czy pr�dko��
	static bool isValidSpeed(std::string text);
	// Sprawdzamy ile 0 doda�
	static bool isValidTwo(std::string text);
	static bool isValidThree(std::string text);
};