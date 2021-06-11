#pragma once
#include "Utility/Timer.h"
class State
{
protected:
	sf::RenderWindow& window;
	std::stack<State*>& states;

	bool quit;

	/*float keytime;
	float keytimeMax;*/
	Timer keyTimer;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	int scroll;
	bool scrollActive;

	sf::Music music;
	std::map<std::string, std::string>& config;

public:
	State(sf::RenderWindow& window, std::stack<State*>& states, std::map<std::string, std::string>& config);
	virtual ~State();

	//Accesors
	const bool GetQuit() const;
	const bool GetKeytime();

	//Functions
	virtual void EndState();
	virtual void UpdateMousePosition(sf::View* view = nullptr);
	virtual void UpdateScrollWheel(int ticks);
	virtual void ResetScrollWheel();
	virtual void UpdateKeytime(const float dt);
	virtual void UpdateInput(const float dt) = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render(sf::RenderTarget& target) const = 0;
};

