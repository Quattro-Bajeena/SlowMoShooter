#pragma once
#include "MenuState.h"

class GameState;

class EndScreenState :
    public State
{

	sf::Texture wonTexture;
	sf::Texture lostTexture;

	sf::Sprite background;

	sf::Font font;
	sf::Text restartText;
	sf::Text exitText;
	SelectedButton selectedButton;
	sf::Color selectedColor;
	sf::Color defaultColor;


	void Restart();

public:
	EndScreenState(bool won, sf::RenderWindow& window, std::stack<State*>& states);
	virtual void UpdateInput(const float dt) override;
	virtual void Update(const float dt) override;
	virtual void Render(sf::RenderTarget& target) const override;
};

