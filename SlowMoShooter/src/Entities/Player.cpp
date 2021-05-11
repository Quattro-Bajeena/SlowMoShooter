#include "stdafx.h"
#include "Player.h"

Player::Player() :
	Entity()
{
	
	health = 10;
	healthMax = 10;
	dead = false;

	maxVelocity = 500;


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
}

void Player::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
}
