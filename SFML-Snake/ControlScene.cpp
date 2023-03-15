#include "ControlScene.h"
#include "Engine.h"
#include "InputManager.h"
#include "MenuScene.h"

void ControlScene::Init()
{
	Engine* engine = Engine::GetInstance();
	sf::Vector2i windowSize = engine->GetWindowSize();

	// Wyœwietlanie tekstu
	std::shared_ptr<sf::Text> controlsTitle = engine->InitText("RULES");
	controlsTitle->setCharacterSize(60);
	controlsTitle->setPosition(windowSize.x / 2 - controlsTitle->getLocalBounds().width / 2, 60.f);

	std::shared_ptr<sf::Text> controlsText = engine->InitText("In the game of Snake, the player uses arrow");
	controlsText->setCharacterSize(16);
	controlsText->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 180.f);

	std::shared_ptr<sf::Text> controlsText2 = engine->InitText("or WSAD keys to move a character around the ");
	controlsText2->setCharacterSize(16);
	controlsText2->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 220.f);

	std::shared_ptr<sf::Text> controlsText3 = engine->InitText("board.");
	controlsText3->setCharacterSize(16);
	controlsText3->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 260.f);

	std::shared_ptr<sf::Text> controlsText4 = engine->InitText("As the snake eats food, it grows larger.");
	controlsText4->setCharacterSize(16);
	controlsText4->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 300.f);

	std::shared_ptr<sf::Text> controlsText5 = engine->InitText("The game ends when the snake runs");
	controlsText5->setCharacterSize(16);
	controlsText5->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 340.f);

	std::shared_ptr<sf::Text> controlsText6 = engine->InitText("into the screen border or itself.");
	controlsText6->setCharacterSize(16);
	controlsText6->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2, 380.f);

	std::shared_ptr<sf::Text> exitText = engine->InitText("Exit");
	exitText->setCharacterSize(20);
	exitText->setPosition(windowSize.x / 2 - exitText->getLocalBounds().width / 2.f, windowSize.y - 60.f);
	exitText->setFillColor(sf::Color::Red);

	// Wyœwietlamy obrazek
	std::shared_ptr<sf::Sprite> image = engine->InitImage("Images\\book.png");
	image->setPosition(windowSize.x / 2 - image->getLocalBounds().width / 2.f, 440.f);
}

void ControlScene::Update(float deltaTime)
{
}

void ControlScene::UpdateInput()
{
	// Powrót do menu
	if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
	{
		Engine::GetInstance()->LoadScene<MenuScene>();
	}
}