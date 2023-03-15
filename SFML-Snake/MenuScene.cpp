#include "MenuScene.h"
#include "InputManager.h"
#include "Engine.h"
#include "GameScene.h"
#include "GameData.h"
#include "Utils.h"
#include "ControlScene.h"
#include "ScoreBoard.h"

void MenuScene::Init()
{
	// Tworzymy obiekt i ustawiamy parametry
	Engine* engine = Engine::GetInstance();
	sf::Vector2i windowSize = engine->GetWindowSize();
	float cellSize = engine->GetCellSize();

	// Ustawiamy t³o
	engine->SetBackground("Images\\back.jpg", 800, 600);

	// Do czytania wyników
	GameData::ReadHighScores();

	float space = 20.f;
	// Wyœwietlamy teksty w menu
	std::shared_ptr<sf::Text> titleText = engine->InitText("SNAKE");
	titleText->setCharacterSize(100);
	titleText->setPosition(windowSize.x / 2 - titleText->getLocalBounds().width / 2.f, windowSize.y / 3.f);
	startText = engine->InitText("Play");
	startText->setCharacterSize(20);
	startText->setPosition(windowSize.x / 2 - startText->getLocalBounds().width / 2.f, windowSize.y - 200.f);
	scoreText = engine->InitText("Score");
	scoreText->setCharacterSize(20);
	scoreText->setPosition(windowSize.x / 2 - scoreText->getLocalBounds().width / 2.f, windowSize.y - 160.f);
	controlsText = engine->InitText("Rules");
	controlsText->setCharacterSize(20);
	controlsText->setPosition(windowSize.x / 2 - controlsText->getLocalBounds().width / 2.f, windowSize.y - 120.f);
	exitText = engine->InitText("Exit");
	exitText->setCharacterSize(20);
	exitText->setPosition(windowSize.x / 2 - exitText->getLocalBounds().width / 2.f, windowSize.y - 80.f);

	// Ustawiamy wê¿a który krêci siê wokó³ napisu menu
	menuSnakePatrolBounds = sf::FloatRect(titleText->getPosition().x - cellSize - space, titleText->getPosition().y - cellSize - space,
		titleText->getLocalBounds().width + cellSize + space, titleText->getLocalBounds().height + cellSize + space);
	snake = std::make_shared<Snake>(Snake(12, cellSize / 2.f, sf::Vector2f(menuSnakePatrolBounds.left, menuSnakePatrolBounds.top), sf::Vector2i(1, 0)));
	engine->RegisterDrawable(snake);
	engine->RegisterUpdatable(snake);
}

void MenuScene::UpdateInput()
{
	// Poruszanie siê po menu z wykorzystaniem klawiatury
	// Jeœli wybierzemy opcjê start zaczynamy grê
	if (isStartButtonSelected)
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Down) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::S))
		{
			isStartButtonSelected = false;
			isScoreButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->LoadScene<GameScene>();
		}
	}

	// Jeœli wybierzemy opcjê punkty, przechodzimy do Scoreboard
	else if (isScoreButtonSelected)
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Up) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::W))
		{
			isScoreButtonSelected = false;
			isStartButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Down) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::S))
		{
			isScoreButtonSelected = false;
			isControlsButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->LoadScene<ScoreBoard>();
		}
	}

	// Jeœli wybierzemy opcjê zasady, przechodzimy do ControlScene
	else if (isControlsButtonSelected)
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Up) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::W))
		{
			isControlsButtonSelected = false;
			isScoreButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Down) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::S))
		{
			isControlsButtonSelected = false;
			isExitButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->LoadScene<ControlScene>();
		}
	}

	// Wyjœcie z programu
	else if (isExitButtonSelected)
	{
		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Up) || InputManager::WasKeyPressedThisFrame(sf::Keyboard::W))
		{
			isExitButtonSelected = false;
			isControlsButtonSelected = true;
		}

		if (InputManager::WasKeyPressedThisFrame(sf::Keyboard::Enter))
		{
			Engine::GetInstance()->Quit();
		}
	}
}

void MenuScene::Update(float deltaTime)
{
	// Zmiana kierunku przemieszczania siê wê¿a gdy dojdzie do krawêdzi napisu
	sf::Vector2i direction = snake->GetDirection();
	sf::Vector2f snakeHeadPosition = snake->GetHeadPosition();
	if (direction.x > 0.f && snakeHeadPosition.x >= menuSnakePatrolBounds.left + menuSnakePatrolBounds.width ||
		direction.y > 0.f && snakeHeadPosition.y >= menuSnakePatrolBounds.top + menuSnakePatrolBounds.height ||
		direction.x < 0.f && snakeHeadPosition.x <= menuSnakePatrolBounds.left ||
		direction.y < 0.f && snakeHeadPosition.y <= menuSnakePatrolBounds.top)
	{
		sf::Vector2i newDirection = sf::Vector2i(-snake->GetDirection().y, snake->GetDirection().x);
		snake->SetDirection(newDirection);
	}

	// W zale¿noœci od wyboru odpowiednie opcje s¹ podœwietlane na czerwono,
	if (isStartButtonSelected)
	{
		startText->setFillColor(sf::Color::Red);
		scoreText->setFillColor(sf::Color::White);
		controlsText->setFillColor(sf::Color::White);
		exitText->setFillColor(sf::Color::White);
	}
	else if (isScoreButtonSelected)
	{
		scoreText->setFillColor(sf::Color::Red);
		controlsText->setFillColor(sf::Color::White);
		startText->setFillColor(sf::Color::White);
		exitText->setFillColor(sf::Color::White);
	}
	else if (isControlsButtonSelected)
	{
		controlsText->setFillColor(sf::Color::Red);
		scoreText->setFillColor(sf::Color::White);
		startText->setFillColor(sf::Color::White);
		exitText->setFillColor(sf::Color::White);
	}
	else if (isExitButtonSelected)
	{
		exitText->setFillColor(sf::Color::Red);
		scoreText->setFillColor(sf::Color::White);
		controlsText->setFillColor(sf::Color::White);
		startText->setFillColor(sf::Color::White);
	}
}