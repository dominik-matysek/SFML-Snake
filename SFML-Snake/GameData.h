#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>

// Klasa do obs³ugi plików z wynikami
class GameData
{
private:

	GameData();

public:
	static int Score;
	static int HighScore;
	static std::filesystem::path image_path;

	// Wektor do przechowywania najlepszych wyników
	static std::vector<int> vec;
	// Wczytanie najlepszych wyników
	static void ReadHighScores();
	// Zapisanie wyniku do pliku
	static void SaveHighScore();

	// Sprawdzanie czy plik z wynikami jest pusty
	static bool is_empty(std::ifstream& file);

	// W zale¿noœci od tego, czy aktualny wynik gracza pobi³ rekord, wynik ma inny kolor
	static sf::Color GetScoreColor();
};