#include "stdafx.h"
#include "GameState.h"


void GameState::EndState()
{
	//states.push(new EndScreenState(stateData, statistics, audio));
	quit = true;
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
		
		sf::Vector2f pos = sf::Vector2f(RNG::get().randomF(0, 5000), RNG::get().randomF(0, 3000));
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

void GameState::UpdateGui(const float dt)
{
	playerHealth.setString(std::to_string(player->GetHealth()));
	timeSlowBar.setScale(timeSlowGauge / timeSlowLimit, 1);
}



GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states)
	:State(window, states)
{
	renderTexture.create(1920, 1080);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
	view.zoom(2);

	player = std::make_unique<Player>(sf::Vector2f());
	player->SetPosition(sf::Vector2f(0, 0));

	enemyTexture.loadFromFile("Assets/UN.png");

	backgroundTexture.loadFromFile("Assets/background.jpg");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
	background.setScale(5, 5);

	enemyTimer = Timer(1);

	

	usingTimeSlow = false;
	timeSlow = false;
	timeSlowLimit = 8;
	timeSlowGauge = timeSlowLimit;
	timeSlowThreshold = timeSlowLimit * 0.75;

	slowTimeMultiplier = 0.1;
	currentTimeMultiplier = 1;
	gaugeDepletionSpeed = 2;

	font.loadFromFile("Assets/font.ttf");

	playerHealth.setFont(font);
	playerHealth.setPosition(10, 10);
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

	

	UpdateView(dt);
	UpdateGui(dt);

	if (player->IsDead())
		EndState();

	ResetScrollWheel();
}

void GameState::RenderGui(sf::RenderTarget& target) const
{
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

	RenderGui(renderTexture);

	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture());
	
	target.draw(renderSprite);
}
