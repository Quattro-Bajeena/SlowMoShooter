#include "stdafx.h"
#include "Player.h"

Player::Player() :
	Entity()
{
	
	health = 10;
	healthMax = 10;
	dead = false;
	dashing = false;

	acceleration = 4000;
	deceleration = 5000;
	maxVelocity = maxVelocityDefault = 1000;

	dashVelocity = 1000;


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
	if (this->invincibility == false) {
		this->health -= damage;
	}
}

void Player::LooseHealthInv(int damage)
{
	if (this->invincibility == false) {
		this->health -= damage;
		this->invincibility = true;
		this->invincibilityTimer = 0.f;
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
	dashing = true;
	maxVelocity = dashVelocity;
	velocity = util::Normalize(velocity) * dashVelocity;
}

void Player::EndDash()
{
	dashing = false;
	maxVelocity = maxVelocityDefault;
}

void Player::Update(const float dt)
{
	this->invincibilityTimer += dt;

	if (this->invincibility == true && this->invincibilityTimer >= this->invincibilityTimerMax) {
		this->invincibility = false;
		this->invincibilityTimer = 0.f;
	}
	if (this->health <= 0) {
		this->dead = true;
	}

	UpdateMovement(dt);
}

void Player::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
}
