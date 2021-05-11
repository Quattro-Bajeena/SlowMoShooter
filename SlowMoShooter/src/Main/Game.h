#pragma once
#include "States/State.h"
#include "States/GameState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	float dt; //Delat Time - time between frames

	std::stack<State*> states;

	void UpdateSFMLEvents();
	void Update();

	void Render() const;

public:
	Game();
	~Game();

	void Run();

};

