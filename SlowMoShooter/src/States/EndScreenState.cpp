#include "stdafx.h"
#include "EndScreenState.h"
#include "GameState.h"

void EndScreenState::Restart()
{
	states.push(new GameState(window, states));
	EndState();
}

EndScreenState::EndScreenState(bool won, sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	wonTexture.loadFromFile("Assets/WonBackgorund.jpg");
	lostTexture.loadFromFile("Assets/LostBackground.jpg");
	font.loadFromFile("Assets/Helvetica-Bold.ttf");

	restartText.setFont(font);
	exitText.setFont(font);


	restartText.setPosition(600, 600);
	restartText.setScale(2, 2);

	exitText.setScale(2, 2);
	exitText.setPosition(800, 800);

	

	selectedColor = sf::Color::Red;
	defaultColor = sf::Color::Black;

	selectedButton = SelectedButton::play;

	restartText.setFillColor(selectedColor);
	exitText.setFillColor(defaultColor);
	

	if (won) {
		background.setTexture(wonTexture);
		restartText.setString("take on enemies of Lord once again");
		exitText.setString("ascend to the Upper Domain");
	}
	else {
		background.setTexture(lostTexture);
		restartText.setString("come back to live and fight");
		exitText.setString("perish into darkness");
	}


}

void EndScreenState::UpdateInput(const float dt)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && GetKeytime()) {
		if (selectedButton == SelectedButton::play) {
			selectedButton = SelectedButton::exit;
			restartText.setFillColor(defaultColor);
			exitText.setFillColor(selectedColor);

		}
		else if (selectedButton == SelectedButton::exit) {
			selectedButton = SelectedButton::play;
			restartText.setFillColor(selectedColor);
			exitText.setFillColor(defaultColor);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (selectedButton == SelectedButton::play) {
			Restart();
		}
		else if (selectedButton == SelectedButton::exit) {
			EndState();
		}
	}
}

void EndScreenState::Update(const float dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateKeytime(dt);
}

void EndScreenState::Render(sf::RenderTarget& target) const
{
	target.draw(background);
	target.draw(restartText);
	target.draw(exitText);
}
