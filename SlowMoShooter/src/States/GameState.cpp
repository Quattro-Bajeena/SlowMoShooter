#include "stdafx.h"
#include "GameState.h"


void GameState::EndState()
{
	//this->states.push(new EndScreenState(this->stateData, this->statistics, this->audio));
	quit = true;
}

void GameState::UpdateInput(const float dt)
{

}

GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	renderTexture.create(1920, 1080);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
}

GameState::~GameState()
{
}



void GameState::Update(const float dt)
{
}

void GameState::Render(sf::RenderTarget* target) const
{
}
