#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Texture& texture)
	:Entity()
{
	
	health = 1;
	healthMax = 1;
	dead = false;


	acceleration = 6000;
	deceleration = 7000;
	maxVelocity = 1500;

	distanceThreshold = 500;
	points = 1;
	damage = 1;
	
	shootTimer = 0;
	shootTimerMax = 1;

	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(position);
}

const int Enemy::GetPoints() const
{
	return points;
}

void Enemy::Move(const sf::Vector2f& target, const float dt)
{
	float distance = util::Distance(target, GetCenterPosition());

	sf::Vector2f dir;

	if (distance > distanceThreshold) {
		dir = target;
	}
	else if (distance > distanceThreshold * 0.8) {
		dir = sf::Vector2f(0, 0);
	}
	else {
		dir = -target;
	}

	velocity += sf::Vector2f(dir) * acceleration * dt;
}

void Enemy::Shoot(std::list<Bullet>& bullets, sf::Vector2f target)
{
}



void Enemy::Update(const sf::Vector2f& target, const float& dt)
{
	invincibilityTimer += dt;
	shootTimer += dt;

	Move(target, dt);


	if (health <= 0) {
		dead = true;
	}
	UpdateMovement(dt);
}

void Enemy::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
}
