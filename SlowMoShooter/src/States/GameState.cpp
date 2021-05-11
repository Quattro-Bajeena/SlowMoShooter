#include "stdafx.h"
#include "GameState.h"


void GameState::EndState()
{
	//states.push(new EndScreenState(stateData, statistics, audio));
	quit = true;
}

void GameState::UpdateInput(const float dt)
{
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->view.zoom(1 + (0.5f * dt));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->view.zoom(1 - (0.5f * dt));
	}

}

void GameState::UpdatePlayerInput(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player->Move(sf::Vector2f(-1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->Move(sf::Vector2f(1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player->Move(sf::Vector2f(0.f, -1.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->Move(sf::Vector2f(0.f, 1.f), dt);
	}
}

GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	renderTexture.create(1920, 1080);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));

	player = new Player();
	player->SetPosition(sf::Vector2f(0, 0));

}

GameState::~GameState()
{
}



void GameState::Update(const float dt)
{
	UpdateMousePosition(&view);
	UpdateInput(dt);
	UpdateKeytime(dt);



	UpdatePlayerInput(dt);
	player->Update(dt);

	if (player->IsDead())
		EndState();

	ResetScrollWheel();
}

void GameState::Render(sf::RenderTarget& target) const
{
	renderTexture.clear();
	renderTexture.setView(view);

	player->Render(renderTexture);

	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture());
	target.draw(renderSprite);
}
