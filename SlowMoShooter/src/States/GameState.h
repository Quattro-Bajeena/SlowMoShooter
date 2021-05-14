#pragma once
#include "States/State.h"
#include "Entities/Player.h"
#include "Weapons/Bullet.h"

class GameState : public State
{
private:
	sf::View view;
	mutable sf::RenderTexture renderTexture;
	mutable sf::Sprite renderSprite;

	sf::Texture enemyTexture;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	Player* player;

	std::list<Bullet> playerBullets;


	void EndState() override;
	void UpdateView(const float dt);
	void UpdateInput(const float dt) override;
	void UpdatePlayerInput(const float dt);
	//void UpdateGui(const float dt);
	//void UpdatePauseMenuButtons(const float dt);

	//virtual void UpdatePlayerInput(const float dt);
	//void UpdateTileMap(const float dt);

	//void RenderGui(sf::RenderTarget* target = nullptr) const;

public:
	GameState(sf::RenderWindow& window, std::stack<State*>& states);
	~GameState();

	void Update(const float dt) override;
	void Render(sf::RenderTarget& target) const override;



};

