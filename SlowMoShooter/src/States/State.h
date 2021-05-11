#pragma once
class State
{
protected:
	sf::RenderWindow& window;
	std::stack<State*>& states;

	bool quit;

	float keytime;
	float keytimeMax;

	float clickTime;
	float clickTimeMax;

	int gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
	int scroll;
	bool scrollActive;

public:
	State(sf::RenderWindow& window, std::stack<State*>& states);
	virtual ~State();

	//Accesors
	const bool GetQuit() const;
	const bool GetKeytime();
	const bool GetClickTime();

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

