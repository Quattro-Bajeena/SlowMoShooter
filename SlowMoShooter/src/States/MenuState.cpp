#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"

void MenuState::StartGame()
{
	states.push(new GameState(window, states));
}

MenuState::MenuState(sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	backgroundTexture.loadFromFile("Assets/MenuBackground.jpg");
	background.setTexture(backgroundTexture);

	selectedColor = sf::Color::Red;
	defaultColor = sf::Color::Black;

	selectedButton = SelectedButton::play;

	font.loadFromFile("Assets/Helvetica-Bold.ttf");

	playText.setFont(font);
	//playText.setCharacterSize(100);
	playText.setCharacterSize(32);
	playText.setScale(2, 2);
	playText.setString("defeat forces of evil");
	playText.setPosition(1300, 850);
	playText.setFillColor(selectedColor);

	exitText.setFont(font);
	exitText.setCharacterSize(32);
	//exitText.setCharacterSize(100);
	exitText.setScale(2, 2);
	exitText.setString("yield like a coward");
	exitText.setPosition(1300, 950);
	exitText.setFillColor(defaultColor);

	

}

MenuState::~MenuState()
{
}

void MenuState::UpdateInput(const float dt)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && GetKeytime()) {
		if (selectedButton == SelectedButton::play) {
			selectedButton = SelectedButton::exit;
			playText.setFillColor(defaultColor);
			exitText.setFillColor(selectedColor);

		}
		else if (selectedButton == SelectedButton::exit) {
			selectedButton = SelectedButton::play;
			playText.setFillColor(selectedColor);
			exitText.setFillColor(defaultColor);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && GetKeytime()) {
		if (selectedButton == SelectedButton::play) {
			StartGame();
		}
		else if(selectedButton == SelectedButton::exit){
			EndState();
		}
	}
}

void MenuState::Update(const float dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateKeytime(dt);


}

void MenuState::Render(sf::RenderTarget& target) const
{
	target.draw(background);
	target.draw(exitText);
	target.draw(playText);
}
