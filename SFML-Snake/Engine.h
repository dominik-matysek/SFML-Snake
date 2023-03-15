#pragma once

#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Collidable.h"
#include "Scene.h"

// Klasa zarz¹dzaj¹ca dzia³aniem ca³ego programu
class Engine
{
private:
	// Prywatny konstruktor jak to w singletonach, ³aduje font przy okazji
	Engine();

	static Engine* instance;

	// Okno
	std::shared_ptr<sf::RenderWindow> window;
	sf::Vector2i windowSize = sf::Vector2i(800, 600);

	// Shared pointery, ¿eby wygodnie korzystaæ z wielu wskaŸników wskazuj¹cych ten sam obiekt
	// no i przez wygodny wskaŸnik na licznik obiektów
	std::shared_ptr<Scene> scene = nullptr;
	std::vector<std::shared_ptr<sf::Drawable>> drawables;
	std::vector<std::shared_ptr<Updatable>> updatables;
	std::vector<std::shared_ptr<Collidable>> collidables;

	// Stuff potrzebny do wyœwietlania rzeczy
	float cellSize = 20.f;
	sf::Texture texture;
	sf::Font font;
	sf::Texture background;
	sf::Sprite sprite;

public:
	// Singleton, aby nie istnia³o wiêcej ni¿ 1 instancja obiektu klasy
	static Engine* GetInstance();

	// Destruktor
	~Engine();

	// Start programu
	void Init();

	// Aktualizacja inputów
	void UpdateInput();
	// Aktualizacja obiektów w danej scenie
	void Update(float deltaTime);
	// Wyœwietlanie odpowiednich obiektów (z sf::Drawable, obiekty do rysowania)
	void Render();

	// Do sprawdzania czy okno nie jest zamkniête
	bool IsRunning() const;
	// Do sprawdzania czy okno ma input focus (czy przyjmuje klawisze, bo mo¿e byæ otwartych kilka okien naraz, ale tylko jedno mo¿e odbieraæ to co zostanie wstukane na klawiaturze albo myszce)
	bool HasFocus() const;

	// Do zmiany pozycji z float na "kratkow¹" int
	sf::Vector2i WorldPositionToGridPosition(sf::Vector2f position) const;
	// Do zmiany pozycji obiektu z "kratkowej" int na float
	sf::Vector2f GridPositionToWorldPosition(sf::Vector2i position) const;

	// Do sprawdzania czy obiekty mog¹ce wejœæ ze sob¹ w kolizjê siê zderzy³y
	bool Collides(sf::Vector2i gridPosition) const;

	// Do za³adowania konkretnej sceny w grze
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

	// Do ustawiania t³a dla poszczególnych scen
	void SetBackground(const std::string& content, int x, int y);

	// Do ustawiania tekstów wyœwietlanych na ekranie
	std::shared_ptr<sf::Text> InitText(const std::string& content);
	// Do ustawiania obrazków wyœwietlanych na ekranie
	std::shared_ptr<sf::Sprite> InitImage(const std::string& content);
	// Do zamiany zawartoœci wektora z wynikami z pliku na string, a nastêpnie na sf::Text
	std::shared_ptr<sf::Text> InitVector(const std::vector<int>& vec);

	// Do zapisania obiektu jako wyœwietlanego w ka¿dej klatce
	void RegisterDrawable(std::shared_ptr<sf::Drawable> drawable);
	// Do zapisania obiektu jako wyœwietlanego i aktualizowanego co ka¿d¹ klatkê
	void RegisterUpdatable(std::shared_ptr<Updatable> updatable);
	// Do zapisania obiektu jako mog¹cego wejœæ w kolizjê, sprawdzany przy u¿yciu Engine::Collides
	void RegisterCollidable(std::shared_ptr<Collidable> collidable);

	// Zwraca wielkoœæ komórki
	float GetCellSize() const;
	// Zwraca wielkoœæ okna
	const sf::Vector2i GetWindowSize() const;
};
