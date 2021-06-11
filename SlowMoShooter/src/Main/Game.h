#pragma once
#include "States/State.h"
#include "States/GameState.h"
#include "States/MenuState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	sf::Image icon;
	float dt; //Delat Time - time between frames

	std::stack<State*> states;
	std::map<std::string, std::string> config;

	void LoadConfig();
	void UpdateSFMLEvents();
	void Update();

	void Render() const;


public:
	Game();
	~Game();

	void Run();

};

