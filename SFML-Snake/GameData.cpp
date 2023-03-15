#include "GameData.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <filesystem>

int GameData::Score = 0;
int GameData::HighScore = 0;
std::vector<int> GameData::vec = {};
// Sta�a �cie�ka do pliku z wynikami z wykorzystaniem biblioteki "filesystem"
std::filesystem::path GameData::image_path("C:\\Users\\domin\\Desktop\\Snake_PK4\\SFML-Snake\\Results\\scores.txt");

bool GameData::is_empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

void GameData::ReadHighScores()
{
	// Na pocz�tku czy�cimy wektor aby warto�ci si� nie powtarza�y
	vec.clear();

	int element;

	std::ifstream file(image_path);
	if (!file.is_open())
	{
		std::cout << "Couldn't open file" << std::endl;
	}

	if (is_empty(file))
	{
		return;
	}

	// Wrzucamy zawarto�� pliku do wektora
	while (file >> element)
	{
		vec.push_back(element);
	}

	// Sortujemy i odwracamy kolejno�� warto�ci w wektorze z u�yciem biblioteki "ranges"
	std::ranges::sort(vec);
	std::ranges::reverse(vec);
	// Usuwamy duplikaty
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	// Usuwamy warto�ci wektora dop�ki nie zostanie 5 najwi�kszych wynik�w
	while (vec.size() > 5)
	{
		vec.pop_back();
	}
	// Pierwsza warto�� w wektorze jest jednocze�nie najwi�ksza
	GameData::HighScore = vec[0];

	file.close();
}

void GameData::SaveHighScore()
{
	std::ofstream file(image_path, std::ios_base::app | std::ios_base::out);
	if (!file.is_open())
	{
		std::cerr << "Couldn't save high score" << std::endl;
		return;
	}

	// Zapisujemy wynik, ka�dy w nowej linii w pliku
	file << GameData::Score << "\n";

	file.close();
}

sf::Color GameData::GetScoreColor()
{
	// Je�eli aktualny wynik gracza wy�szy od rekordu, zmieniamy kolor na zielony
	return Score > HighScore ? sf::Color::Green : sf::Color::Yellow;
}