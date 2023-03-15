#include "MenuScene.h"
#include "Engine.h"
#include "GameData.h"
#include "ScoreBoard.h"
#include "InputManager.h"

void ScoreBoard::Init()
{
	Engine* engine = Engine::GetInstance();
	sf::Vector2i windowSize = engine->GetWindowSize();

	// Wyœwietlanie tekstu
	std::shared_ptr<sf::Text> titleText = engine->InitText("SCOREBOARD");
	titleText->setCharacterSize(60);
	titleText->setPosition(windowSize.x / 2 - titleText->getLocalBounds().width / 2, 60.f);

	std::shared_ptr<sf::Text> titleText_2 = engine->InitText("Top 5 scores");
	titleText_2->setCharacterSize(40);
	titleText_2->setPosition(windowSize.x / 2 - titleText_2->getLocalBounds().width / 2, 160.f);

	std::shared_ptr<sf::Text> exitText = engine->InitText("Exit");
	exitText->setCharacterSize(20);
	exitText->setPosition(windowSize.x / 2 - exitText->getLocalBounds().width / 2.f, windowSize.y - 60.f);
	exitText->setFillColor(sf::Color::Red);

	// Wyœwietlanie wyników zapisanych w wektorze
	std::shared_ptr<sf::Text> finalScoreText = engine->InitVector(GameData::vec);
	finalScoreText->setCharacterSize(30);
	finalScoreText->setPosition(windowSize.x / 2 - finalScoreText->getLocalBounds().width / 2, 240.f);
}

void ScoreBoard::Update(float deltaTime)
{
}

void ScoreBoard::UpdateInput()
{
	// Powrót do menu
	if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
	{
		Engine::GetInstance()->LoadScene<MenuScene>();
	}
}