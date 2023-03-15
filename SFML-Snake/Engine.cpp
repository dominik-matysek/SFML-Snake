#include <iostream>
#include "Engine.h"
#include "InputManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameData.h"

Engine* Engine::instance{ nullptr };

Engine* Engine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Engine();
	}
	return instance;
}

Engine::Engine()
{
	if (!font.loadFromFile("Fonts\\PressStart2P.ttf"))
	{
		std::cout << "Couldn't load font" << std::endl;
	}
}

Engine::~Engine()
{
}

void Engine::Init()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowSize.x, windowSize.y), "Snake", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("Images\\snake.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	LoadScene<MenuScene>();
}

void Engine::UpdateInput()
{
	InputManager::Update();

	if (scene)
	{
		scene->UpdateInput();
	}
}

void Engine::Update(float deltaTime)
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			return;
		}
	}

	for (size_t i = 0; i < updatables.size(); ++i)
	{
		updatables[i]->Update(deltaTime);
	}

	if (scene)
	{
		scene->Update(deltaTime);
	}
}

void Engine::Render()
{
	window->clear();
	window->draw(sprite);

	for (size_t i = 0; i < drawables.size(); ++i)
	{
		window->draw(*drawables[i]);
	}

	window->display();
}

bool Engine::IsRunning() const
{
	return window->isOpen();
}

bool Engine::HasFocus() const
{
	return window->hasFocus();
}

bool Engine::Collides(sf::Vector2i gridPosition) const
{
	for (size_t i = 0; i < collidables.size(); ++i)
	{
		if (collidables[i]->Collides(gridPosition))
		{
			return true;
		}
	}

	return false;
}

void Engine::Quit()
{
	window->close();
}

sf::Vector2i Engine::WorldPositionToGridPosition(sf::Vector2f position) const
{
	sf::Vector2i gridPosition((int)(position.x / cellSize), (int)(position.y / cellSize));
	return gridPosition;
}

sf::Vector2f Engine::GridPositionToWorldPosition(sf::Vector2i position) const
{
	sf::Vector2f worldPosition(position.x * cellSize, position.y * cellSize);
	return worldPosition;
}

void Engine::SetBackground(const std::string& content, int x, int y)
{
	background.loadFromFile(content);

	sprite.setTexture(background);
	sprite.setTextureRect(sf::IntRect(0, 0, x, y));
}

std::shared_ptr<sf::Text> Engine::InitText(const std::string& content)
{
	std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
	text->setFont(font);
	text->setFillColor(sf::Color::White);
	text->setString(content);

	RegisterDrawable(text);

	return text;
}

std::shared_ptr<sf::Text> Engine::InitVector(const std::vector<int>& vec)
{
	std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();

	text->setFont(font);
	text->setFillColor(sf::Color::White);

	std::string content;

	for (int i = 0; i < vec.size(); i++)
	{
		content += std::to_string(i + 1) + ". " + std::to_string(vec[i]) + " points\n\n";
	}

	text->setString(content);
	RegisterDrawable(text);

	return text;
}

std::shared_ptr<sf::Sprite> Engine::InitImage(const std::string& content)
{
	std::shared_ptr<sf::Sprite> image = std::make_shared<sf::Sprite>();
	texture.loadFromFile(content);
	image->setTexture(texture);

	RegisterDrawable(image);

	return image;
}

void Engine::RegisterDrawable(std::shared_ptr<sf::Drawable> drawable)
{
	drawables.push_back(drawable);
}

void Engine::RegisterUpdatable(std::shared_ptr<Updatable> updatable)
{
	updatables.push_back(updatable);
}

void Engine::RegisterCollidable(std::shared_ptr<Collidable> collidable)
{
	collidables.push_back(collidable);
}

float Engine::GetCellSize() const
{
	return cellSize;
}

const sf::Vector2i Engine::GetWindowSize() const
{
	return windowSize;
}