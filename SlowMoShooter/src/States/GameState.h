#pragma once
#include "States/EndScreenState.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Weapons/Bullet.h"
#include "Enviroment/Map.h"
#include "Enviroment/Objective.h"
#include "UI/Arrow.h"


class GameState : public State
{
private:
	sf::View view;
	mutable sf::RenderTexture renderTexture;
	mutable sf::Sprite renderSprite;

	sf::Texture enemyTexture;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	std::unique_ptr<Map> map;
	
	
	std::vector<Objective> objectives;
	std::vector<Arrow> objectiveArrows;
	sf::Texture arrowTexture;
	sf::Texture objectiveDeactivatedTexture;
	sf::Texture objectiveActivatedTexture;

	sf::Text playerHealth;

	std::unique_ptr<Player> player;
	std::list<Bullet> playerBullets;

	std::list<std::unique_ptr<Enemy>> enemies;
	std::list<Bullet> enemyBullets;

	int maxNoEnemies;
	Timer enemyTimer;
	sf::Font font;

	sf::RectangleShape timeSlowBar;
	sf::RectangleShape timeSlowBarOutline;
	sf::RectangleShape timeSlowBarBackground;

	// Time slow mechanic
	bool usingTimeSlow; //indcates if button for using slow is pressed
	bool timeSlow; // if slow is actually active
	float gaugeDepletionSpeed; // how fast gauge is used up comapred to recovery
	float timeSlowLimit; // max gauge value - no. of seconds to recover
	float timeSlowGauge; //current level of timeSlow left
	float timeSlowThreshold; // minum level of gauge you have to be able to activate time slow
	float currentTimeMultiplier;
	float slowTimeMultiplier;

	void WinGame();
	void LoseGame();
	void UpdateView(const float dt);
	void UpdateInput(const float dt) override;
	void UpdatePlayerInput(const float dt);

	void SpawnEnemies(const float dt);
	void UpdateEnemies(const float dt);
	void UpdatePlayer(const float dt);
	void UpdatePlayerBullets(const float dt);
	void UpdateMap(const float dt);
	void UpdateGui(const float dt);
	//void UpdatePauseMenuButtons(const float dt);

	//virtual void UpdatePlayerInput(const float dt);
	//void UpdateTileMap(const float dt);

	void RenderGui(sf::RenderTarget& target) const;

public:
	GameState(sf::RenderWindow& window, std::stack<State*>& states, std::map<std::string, std::string>& config);
	~GameState();

	void Update(const float dt) override;
	void Render(sf::RenderTarget& target) const override;



};

