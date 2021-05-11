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
	sf::Vector2i dir = sf::Vector2i(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dir += sf::Vector2i(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir += sf::Vector2i(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dir += sf::Vector2i(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dir += sf::Vector2i(0, 1), dt;
	}

	player->Move(dir, dt);
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
