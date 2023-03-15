#include "GameScene.h"
#include "InputManager.h"
#include "Engine.h"
#include "EndscreenScene.h"
#include "GameData.h"
#include "Utils.h"

void GameScene::Init()
{
	// Resetowanie wartoœci losowej (do pojawiania siê jab³ka)
	srand((unsigned int)time(NULL));

	Engine* engine = Engine::GetInstance();

	sf::Vector2i windowSize = engine->GetWindowSize();
	float cellSize = engine->GetCellSize();

	engine->SetBackground("Images\\tlo.jpg", 800, 500);

	// Ustalenie wielkoœci kratki
	_gridSize = sf::Vector2i(windowSize.x / (int)cellSize, (windowSize.y - _gameUiHeight) / (int)cellSize);

	// Resetowanie punktów oraz czasu
	GameData::Score = 0;
	_timeElapsed = 0.f;
	_gameOverTimer = 0;

	// Tworzenie granicy z uwzglêdnieniem obszaru zajmowanego przez UI
	_border = std::make_shared<Border>(_gridSize, sf::Vector2i(windowSize.x, windowSize.y - _gameUiHeight));
	engine->RegisterDrawable(_border);
	engine->RegisterCollidable(_border);

	// Tworzenie postaci gracza
	_player = std::make_shared<Snake>(Snake(3, cellSize / 2.f, sf::Vector2f((_gridSize.x / 2) * cellSize, (_gridSize.y / 2) * cellSize), sf::Vector2i(1, 0)));
	engine->RegisterDrawable(_player);
	engine->RegisterUpdatable(_player);
	engine->RegisterCollidable(_player);

	// Tworzenie przedmiotu do zbierania
	_fruit = std::make_shared<Fruit>(sf::Vector2f(cellSize, cellSize), _gridSize);
	engine->RegisterDrawable(_fruit);
	_fruit->Spawn();
	_player->SetFruit(_fruit);

	// UI
	float horizontalPadding = 40.f;
	float space = 10.f;

	// Wyœwietlanie czasu
	std::shared_ptr<sf::Text> timeLabel = engine->InitText("Time");
	_timeText = engine->InitText(Utils::GetFormattedNumericString(std::to_string(0)));
	timeLabel->setCharacterSize(24);
	_timeText->setCharacterSize(24);
	timeLabel->setPosition(horizontalPadding, windowSize.y - _gameUiHeight / 2.f - (timeLabel->getLocalBounds().height + _timeText->getLocalBounds().height + space) / 2.f);
	_timeText->setPosition(timeLabel->getPosition().x + (timeLabel->getLocalBounds().width - _timeText->getLocalBounds().width) / 2.f,
		timeLabel->getPosition().y + timeLabel->getLocalBounds().height + space);

	// Wyœwietlanie punktacji
	_scoreLabel = engine->InitText("Score");
	_scoreText = engine->InitText(Utils::GetFormattedNumericString(std::to_string(0)));
	_scoreLabel->setCharacterSize(35);
	_scoreText->setCharacterSize(35);
	// Zmiana koloru je¿eli gracz pobi³ rekord
	_scoreLabel->setFillColor(GameData::GetScoreColor());
	_scoreText->setFillColor(GameData::GetScoreColor());
	_scoreLabel->setPosition(windowSize.x / 2.f - _scoreLabel->getLocalBounds().width / 2.f,
		windowSize.y - _gameUiHeight / 2.f - (_scoreLabel->getLocalBounds().height + _scoreText->getLocalBounds().height + space) / 2.f);
	_scoreText->setPosition(windowSize.x / 2.f - _scoreText->getLocalBounds().width / 2.f, _scoreLabel->getPosition().y + _scoreLabel->getLocalBounds().height + space);

	// Wyœwietlanie prêdkoœci
	_speedLabel = engine->InitText("Speed");
	_speedText = engine->InitText(Utils::GetFormattedNumericString(std::to_string(1.f)));
	_speedLabel->setCharacterSize(24);
	_speedText->setCharacterSize(24);
	_speedLabel->setPosition(windowSize.x - _speedLabel->getLocalBounds().width - horizontalPadding,
		windowSize.y - _gameUiHeight / 2.f - (_speedLabel->getLocalBounds().height + _speedText->getLocalBounds().height + space) / 2.f);
	_speedText->setPosition(_speedLabel->getPosition().x + (_speedLabel->getLocalBounds().width - _speedText->getLocalBounds().width) / 2.f,
		_speedLabel->getPosition().y + _speedLabel->getLocalBounds().height + space);
}

void GameScene::UpdateInput()
{
	// Zmiana kierunku poruszania siê gracza
	if (InputManager::IsKeyPressed(sf::Keyboard::W) || InputManager::IsKeyPressed(sf::Keyboard::Up))
	{
		_player->SetDirection(sf::Vector2i(0, -1));
	}
	else if (InputManager::IsKeyPressed(sf::Keyboard::S) || InputManager::IsKeyPressed(sf::Keyboard::Down))
	{
		_player->SetDirection(sf::Vector2i(0, 1));
	}
	else if (InputManager::IsKeyPressed(sf::Keyboard::D) || InputManager::IsKeyPressed(sf::Keyboard::Right))
	{
		_player->SetDirection(sf::Vector2i(1, 0));
	}
	else if (InputManager::IsKeyPressed(sf::Keyboard::A) || InputManager::IsKeyPressed(sf::Keyboard::Left))
	{
		_player->SetDirection(sf::Vector2i(-1, 0));
	}
}

void GameScene::Update(float deltaTime)
{
	// Je¿eli gracz ¿yje
	if (!_player->IsDead())
	{
		// Aktualizowanie czasu i odpowiednie wyœwietlanie
		_timeElapsed += deltaTime;
		_timeText->setString(Utils::GetFormattedNumericString(std::to_string((int)_timeElapsed)));

		// Aktualizowanie punktacji
		_scoreText->setString(Utils::GetFormattedNumericString(std::to_string(GameData::Score)));
		_scoreLabel->setFillColor(GameData::GetScoreColor());
		_scoreText->setFillColor(GameData::GetScoreColor());

		// Aktualizowanie prêdkoœci
		_speedText->setString(Utils::GetFormattedNumericString(std::to_string(_player->GetMoveSpeed())));
		// Gdy gracz osi¹gnie prêdkoœc maksymaln¹, zmiana koloru
		sf::Color speedColor = _player->ReachedMaxSpeed() ? sf::Color(185, 45, 185) : sf::Color::White;
		_speedText->setFillColor(speedColor);
		_speedLabel->setFillColor(speedColor);
	}

	// Œmieræ gracza, po krótkim opóŸnieniu przejœcie do EndscreenScene
	else
	{
		_gameOverTimer += deltaTime;

		if (_gameOverTimer >= _gameOverDelay)
		{
			Engine::GetInstance()->LoadScene<EndscreenScene>();
		}
	}
}