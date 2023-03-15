#include "EndscreenScene.h"
#include "InputManager.h"
#include "Engine.h"
#include "MenuScene.h"
#include "GameData.h"
#include "Utils.h"

void EndscreenScene::Init()
{
	Engine* engine = Engine::GetInstance();
	sf::Vector2i windowSize = engine->GetWindowSize();

	engine->SetBackground("Images\\back.jpg", 800, 600);

	// Wyœwietlanie tekstu i ikonki
	std::shared_ptr<sf::Text> gameOverText = engine->InitText("GAME OVER");
	gameOverText->setCharacterSize(60);
	gameOverText->setPosition(windowSize.x / 2 - gameOverText->getLocalBounds().width / 2, 60.f);
	menuText = engine->InitText("Main Menu");
	menuText->setCharacterSize(20);
	menuText->setPosition(windowSize.x / 2 - menuText->getLocalBounds().width / 2, windowSize.y - 120.f);
	exitText = engine->InitText("Exit");
	exitText->setCharacterSize(20);
	exitText->setPosition(windowSize.x / 2 - exitText->getLocalBounds().width / 2, windowSize.y - 60.f);

	std::shared_ptr<sf::Sprite> image = engine->InitImage("Images\\death3.png");
	image->setPosition(windowSize.x / 2 - image->getLocalBounds().width / 2.f, windowSize.y - 440.f);

	// Wyœwietlanie wyniku
	std::shared_ptr<sf::Text> finalScoreLabel = engine->InitText("Score");
	std::shared_ptr<sf::Text> finalScoreText = engine->InitText(Utils::GetFormattedNumericString(std::to_string(GameData::Score)));
	finalScoreLabel->setCharacterSize(40);
	finalScoreText->setCharacterSize(40);
	// Kolor wyniku zmienia siê w zale¿noœci od tego czy gracz pobi³ rekord
	finalScoreLabel->setFillColor(GameData::GetScoreColor());
	finalScoreText->setFillColor(GameData::GetScoreColor());

	finalScoreLabel->setPosition(windowSize.x / 2 - finalScoreLabel->getLocalBounds().width / 2.f,
		windowSize.y - 260.f);
	finalScoreText->setPosition(windowSize.x / 2 - finalScoreText->getLocalBounds().width / 2.f,
		finalScoreLabel->getPosition().y + finalScoreLabel->getLocalBounds().height + 10.f);

	// Je¿eli gracz pobi³ rekord pojawiaj¹ siê dodatkowe informacje
	if (GameData::Score > GameData::HighScore)
	{
		std::shared_ptr<sf::Text> beatHighscoreText = engine->InitText("You beat the high score !");
		beatHighscoreText->setCharacterSize(20);
		beatHighscoreText->setFillColor(sf::Color::Green);

		float offset = (beatHighscoreText->getLocalBounds().height + 25.f) / 2.f;

		finalScoreLabel->setPosition(finalScoreLabel->getPosition().x, finalScoreLabel->getPosition().y - offset);
		finalScoreText->setPosition(finalScoreText->getPosition().x, finalScoreText->getPosition().y - offset);
		beatHighscoreText->setPosition(windowSize.x / 2 - beatHighscoreText->getLocalBounds().width / 2.f,
			finalScoreText->getPosition().y + finalScoreText->getLocalBounds().height + 25.f);
	}
	GameData::SaveHighScore();
}

void EndscreenScene::UpdateInput()
{
	// Powró do menu
	if (isMenuButtonSelected)
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Down) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::S))
		{
			isMenuButtonSelected = false;
			isExitButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->LoadScene<MenuScene>();
		}
	}

	// Wyjœcie z programu
	else
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Up) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::W))
		{
			isExitButtonSelected = false;
			isMenuButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->Quit();
		}
	}
}

void EndscreenScene::Update(float deltaTime)
{
	// Zmiana podœwietlenia tekstu
	if (isMenuButtonSelected)
	{
		menuText->setFillColor(sf::Color::Red);
		exitText->setFillColor(sf::Color::White);
	}
	else
	{
		exitText->setFillColor(sf::Color::Red);
		menuText->setFillColor(sf::Color::White);
	}
}