#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Vector2f pos) :
	Entity(pos)
{
	
	health = 10;
	healthMax = 10;
	dead = false;
	dashing = false;

	dashTimer = Timer(0.15);
	dashRechargeTimer = Timer(0.5);

	acceleration = 6000;
	deceleration = 7000;
	maxVelocity = maxVelocityDefault = 1500;

	dashVelocity = 7000;

	shootTimer = Timer(1);

	texture.loadFromFile("Assets/schizo.png");
	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(0, 0);
}

Player::~Player()
{
}

void Player::LooseHealth(int damage)
{
	if (invincibility == false) {
		health -= damage;
	}
}

void Player::LooseHealthInv(int damage)
{
	if (invincibility == false) {
		health -= damage;
		invincibility = true;
		invincibilityTimer = 0.f;
	}
}

void Player::Move(const sf::Vector2i dir, const float dt)
{
	inputDir = dir;
	if (dashing == false) {
		velocity += sf::Vector2f(dir) * acceleration * dt;
	}
}

void Player::StartDash()
{
	if (dashing == false &&
		dashRechargeTimer.Ready() &&
		util::VectorLength(sf::Vector2f(inputDir)) != 0.f
		) {

		dashing = true;
		maxVelocity = dashVelocity;
		velocity = util::Normalize(sf::Vector2f(inputDir)) * dashVelocity;
		invincibility = true;
		dashTimer.Reset();
	}
	
}

void Player::EndDash()
{
	dashing = false;
	maxVelocity = maxVelocityDefault;
	dashRechargeTimer.Reset();
}

void Player::Shoot(std::list<Bullet>& bullets, sf::Vector2f target)
{
	if (shootTimer.Ready()) {
		sf::Vector2f start_pos = GetCenterPosition();
		sf::Vector2f direction = util::Normalize(target - start_pos);
		sf::Color color = sf::Color(0, 255, 0);
		int damage = 1;
		float radius = 20;
		float speed = 5000;
		float distance = 5000;

		bullets.emplace_back(start_pos, direction, color, damage, radius, speed, distance);
	}
	
}

void Player::Update(const float dt)
{
	invincibilityTimer.Update(dt);
	dashTimer.Update(dt);
	dashRechargeTimer.Update(dt);
	shootTimer.Update(dt);

	if (dashing == true && dashTimer.Ready()) {
		EndDash();
	}
	if (invincibility == true && invincibilityTimer.Ready()) {
		invincibility = false;
	}
	if (health <= 0) {
		dead = true;
	}

	UpdateMovement(dt);
}

void Player::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
}
