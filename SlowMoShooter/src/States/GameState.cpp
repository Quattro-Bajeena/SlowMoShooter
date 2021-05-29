#include "stdafx.h"
#include "GameState.h"


void GameState::WinGame()
{
	states.push(new EndScreenState(true, window, states));
	EndState();
}

void GameState::LoseGame()
{
	states.push(new EndScreenState(false, window, states));
	EndState();
}


void GameState::UpdateView(const float dt)
{
	view.setCenter(player->GetCenterPosition());
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		for (int i = 0; i < objectives.size(); i++) {
			bool activated = objectives[i].Activate(player->GetCenterPosition());
			if (activated) {
				objectiveArrows[i].Deactivate();
			}
		}
	}


	player->Move(dir, dt);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		player->StartDash();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player->Shoot(playerBullets, mousePosView);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		usingTimeSlow = true;
	}
	else {
		usingTimeSlow = false;
	}
	
}

void GameState::SpawnEnemies(const float dt)
{
	enemyTimer.Update(dt);

	if (enemyTimer.Ready()) {
		sf::Vector2f playerPos = player->GetCenterPosition();
		float range = 3000;
		sf::Vector2f pos = sf::Vector2f(
			RNG::get().randomF(playerPos.x- range, playerPos.x + range), 
			RNG::get().randomF(playerPos.y - range, playerPos.y + range)
		);
		std::unique_ptr<Enemy> new_enemy = std::make_unique<Enemy>(pos, enemyTexture);
		enemies.emplace_back(std::move(new_enemy));
	}
}

void GameState::UpdateEnemies(const float dt)
{
	for (auto&& enemy : enemies) {
		enemy->Update(player->GetCenterPosition(), dt);
		enemy->Shoot(enemyBullets, player->GetCenterPosition());
	}

	for (Bullet& bullet : enemyBullets) {
		bullet.Update(dt);

		if (bullet.CheckCollision(player->GetGlobalBounds())) {
			player->LooseHealthInv(bullet.GetDamage());
			bullet.RegisterHit();
		}
	}

	enemyBullets.remove_if([](const Bullet& b) {return b.ToBeRemoved() == true; });
	enemies.remove_if([](const auto& enemy) {return enemy->IsDead(); });
}

void GameState::UpdatePlayer(const float dt)
{
	player->Update( mousePosView,dt);

	
}

void GameState::UpdatePlayerBullets(const float dt)
{
	for (Bullet& bullet : playerBullets) {
		bullet.Update(dt);

		for (auto&& enemy : enemies) {
			if (bullet.CheckCollision(enemy->GetGlobalBounds())) {
				enemy->LooseHealth(bullet.GetDamage());
				bullet.RegisterHit();
			}
		}
	}

	playerBullets.remove_if([](const Bullet& b) {return b.ToBeRemoved() == true; });
}

void GameState::UpdateMap(const float dt)
{
	if (map->InBounds(player->GetCenterPosition()) == false) {
		player->LooseHealth(player->GetMaxHealth());
	}
	map->UpdateCollision(player.get(), dt);
	for (auto& bullet : playerBullets) {
		if (map->Collision(bullet.GetBounds())) {
			bullet.RegisterHit();
		}
	}



	for (const std::unique_ptr<Enemy>& enemy : enemies) {
		map->UpdateCollision(enemy.get(), dt);

		if (map->InBounds(enemy->GetCenterPosition()) == false) {
			enemy->LooseHealth(enemy->GetMaxHealth());
		}
	}


	for (auto& bullet : enemyBullets) {
		if (map->Collision(bullet.GetBounds())) {
			bullet.RegisterHit();
		}
	}


	
}

void GameState::UpdateGui(const float dt)
{
	for (int i = 0; i < objectives.size(); i++) {
		objectiveArrows[i].Update(player->GetCenterPosition(), objectives[i].GetPosition());
	}
	playerHealth.setString(std::to_string(player->GetHealth()));
	timeSlowBar.setScale(timeSlowGauge / timeSlowLimit, 1);
}



GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	//Rendering
	renderTexture.create(1920, 1080);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
	view.zoom(2);
	
	//Player and Enemies
	player = std::make_unique<Player>(sf::Vector2f());
	

	enemyTexture.loadFromFile("Assets/UN.png");
	enemyTimer = Timer(1);


	//Map and objectives
	map = std::make_unique<Map>(50, 50, 256);
	objectiveActivatedTexture.loadFromFile("Assets/teslaCoilActive.png");
	objectiveDeactivatedTexture.loadFromFile("Assets/teslaCoilNotActive.png");
	arrowTexture.loadFromFile("Assets/arrow.png");
	player->SetPosition(map->GetRandomPosition());



	int numberObjectives = 3;
	float spawnMargin = 1000;
	float threshold = 1000;
	float arrowRadius = 500;
	for (int i = 0; i < numberObjectives; i++) {

		float x = RNG::get().randomF(spawnMargin, map->GetBounds().width - spawnMargin);
		float y = RNG::get().randomF(spawnMargin, map->GetBounds().height - spawnMargin);
		Objective objective = Objective(x, y, threshold, objectiveDeactivatedTexture, objectiveActivatedTexture);
		objectives.emplace_back(objective);

		objectiveArrows.emplace_back(player->GetCenterPosition(), arrowRadius, arrowTexture);
	}

	

	// Slow Time mechanic
	usingTimeSlow = false;
	timeSlow = false;
	timeSlowLimit = 8;
	timeSlowGauge = timeSlowLimit;
	timeSlowThreshold = timeSlowLimit * 0.75;

	slowTimeMultiplier = 0.1;
	currentTimeMultiplier = 1;
	gaugeDepletionSpeed = 2;

	// UI
	font.loadFromFile("Assets/Helvetica.ttf");

	playerHealth.setFont(font);
	playerHealth.setPosition(10, 60);
	playerHealth.setScale(5, 5);
	playerHealth.setString(std::to_string(player->GetHealth()));
	playerHealth.setFillColor(sf::Color::Red);

	sf::Vector2f pos = sf::Vector2f(20, 20);
	sf::Vector2f size = sf::Vector2f(200, 50);
	timeSlowBar.setPosition(pos);
	timeSlowBar.setSize(size);
	timeSlowBar.setFillColor(sf::Color::Blue);

	timeSlowBarOutline.setPosition(pos);
	timeSlowBarOutline.setSize(size);
	timeSlowBarOutline.setFillColor(sf::Color::Transparent);
	timeSlowBarOutline.setOutlineColor(sf::Color::Black);
	timeSlowBarOutline.setOutlineThickness(2);

	timeSlowBarBackground.setPosition(pos);
	timeSlowBarBackground.setSize(size);
	timeSlowBarBackground.setFillColor(sf::Color::White);
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

	
	// Time slow can only be activat if Gauge is larger than threshold or was already active in previous frame
	if (usingTimeSlow && ((timeSlowGauge > timeSlowThreshold) || timeSlow == true)) {

		timeSlowGauge -= dt * gaugeDepletionSpeed;
		if (timeSlowGauge <= 0) {
			timeSlowGauge = 0;
			currentTimeMultiplier = 1;
			timeSlow = false;
		}
		else {
			currentTimeMultiplier = slowTimeMultiplier;
			timeSlow = true;
		}
	}
	else {
		timeSlow = false;
		currentTimeMultiplier = 1;
		timeSlowGauge += dt;
		if (timeSlowGauge > timeSlowLimit) {
			timeSlowGauge = timeSlowLimit;
		}
	}

	SpawnEnemies(dt);
	UpdateEnemies(dt * currentTimeMultiplier);
	UpdatePlayer(dt);
	UpdatePlayerBullets(dt * currentTimeMultiplier);
	UpdateMap(dt);
	

	UpdateView(dt);
	UpdateGui(dt);

	if (player->IsDead())
		LoseGame();

	bool allObjectivesSet = true;
	for (Objective& objective : objectives) {
		if (objective.IsActivated() == false) {
			allObjectivesSet = false;
			break;
		}
	}
	if (allObjectivesSet) {
		WinGame();
	}

	ResetScrollWheel();
}

void GameState::RenderGui(sf::RenderTarget& target) const
{
	for (const Arrow& arrow : objectiveArrows) {
		arrow.Render(target);
	}

	target.setView(target.getDefaultView());
	target.draw(playerHealth);
	target.draw(timeSlowBarBackground);
	target.draw(timeSlowBar);
	target.draw(timeSlowBarOutline);
	target.setView(view);
}

void GameState::Render(sf::RenderTarget& target) const
{
	renderTexture.clear();
	renderTexture.setView(view);

	renderTexture.draw(background);
	map->Render(renderTexture);

	

	for (const Bullet& bullet: playerBullets) {
		bullet.Render(renderTexture);
	}
	for (const Bullet& bullet : enemyBullets) {
		bullet.Render(renderTexture);
	}
	for (auto&& enemy : enemies) {
		enemy->Render(renderTexture);
	}
	player->Render(renderTexture);

	for (const Objective& objective : objectives) {
		objective.Render(renderTexture);
	}

	RenderGui(renderTexture);

	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture());
	
	target.draw(renderSprite);
}
