#pragma once

#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Collidable.h"
#include "Scene.h"

// Klasa zarz�dzaj�ca dzia�aniem ca�ego programu
class Engine
{
private:
	// Prywatny konstruktor jak to w singletonach, �aduje font przy okazji
	Engine();

	static Engine* instance;

	// Okno
	std::shared_ptr<sf::RenderWindow> window;
	sf::Vector2i windowSize = sf::Vector2i(800, 600);

	// Shared pointery, �eby wygodnie korzysta� z wielu wska�nik�w wskazuj�cych ten sam obiekt
	// no i przez wygodny wska�nik na licznik obiekt�w
	std::shared_ptr<Scene> scene = nullptr;
	std::vector<std::shared_ptr<sf::Drawable>> drawables;
	std::vector<std::shared_ptr<Updatable>> updatables;
	std::vector<std::shared_ptr<Collidable>> collidables;

	// Stuff potrzebny do wy�wietlania rzeczy
	float cellSize = 20.f;
	sf::Texture texture;
	sf::Font font;
	sf::Texture background;
	sf::Sprite sprite;

public:
	// Singleton, aby nie istnia�o wi�cej ni� 1 instancja obiektu klasy
	static Engine* GetInstance();

	// Destruktor
	~Engine();

	// Start programu
	void Init();

	// Aktualizacja input�w
	void UpdateInput();
	// Aktualizacja obiekt�w w danej scenie
	void Update(float deltaTime);
	// Wy�wietlanie odpowiednich obiekt�w (z sf::Drawable, obiekty do rysowania)
	void Render();

	// Do sprawdzania czy okno nie jest zamkni�te
	bool IsRunning() const;
	// Do sprawdzania czy okno ma input focus (czy przyjmuje klawisze, bo mo�e by� otwartych kilka okien naraz, ale tylko jedno mo�e odbiera� to co zostanie wstukane na klawiaturze albo myszce)
	bool HasFocus() const;

	// Do zmiany pozycji z float na "kratkow�" int
	sf::Vector2i WorldPositionToGridPosition(sf::Vector2f position) const;
	// Do zmiany pozycji obiektu z "kratkowej" int na float
	sf::Vector2f GridPositionToWorldPosition(sf::Vector2i position) const;

	// Do sprawdzania czy obiekty mog�ce wej�� ze sob� w kolizj� si� zderzy�y
	bool Collides(sf::Vector2i gridPosition) const;

	// Do za�adowania konkretnej sceny w grze
	template<class T> void LoadScene()
	{
		drawables.clear();
		updatables.clear();
		collidables.clear();
		scene = std::make_shared<T>();
		scene->Init();
	}

	// Koniec gry
	void Quit();

	// Do ustawiania t�a dla poszczeg�lnych scen
	void SetBackground(const std::string& content, int x, int y);

	// Do ustawiania tekst�w wy�wietlanych na ekranie
	std::shared_ptr<sf::Text> InitText(const std::string& content);
	// Do ustawiania obrazk�w wy�wietlanych na ekranie
	std::shared_ptr<sf::Sprite> InitImage(const std::string& content);
	// Do zamiany zawarto�ci wektora z wynikami z pliku na string, a nast�pnie na sf::Text
	std::shared_ptr<sf::Text> InitVector(const std::vector<int>& vec);

	// Do zapisania obiektu jako wy�wietlanego w ka�dej klatce
	void RegisterDrawable(std::shared_ptr<sf::Drawable> drawable);
	// Do zapisania obiektu jako wy�wietlanego i aktualizowanego co ka�d� klatk�
	void RegisterUpdatable(std::shared_ptr<Updatable> updatable);
	// Do zapisania obiektu jako mog�cego wej�� w kolizj�, sprawdzany przy u�yciu Engine::Collides
	void RegisterCollidable(std::shared_ptr<Collidable> collidable);

	// Zwraca wielko�� kom�rki
	float GetCellSize() const;
	// Zwraca wielko�� okna
	const sf::Vector2i GetWindowSize() const;
};
