#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Texture& texture)
	:Entity(position)
{
	
	health = 1;
	healthMax = 1;
	dead = false;

	acceleration = RNG::get().randomF(2500, 3500);
	deceleration = RNG::get().randomF(500, 1000);
	maxVelocity = RNG::get().randomF(400, 700);

	distanceThreshold = RNG::get().randomF(1200, 1800);
	points = 1;
	damage = 1;
	
	shootTimer = Timer(2);

	sprite.setTexture(texture);
	float scale = RNG::get().randomF(0.4, 0.6);
	sprite.setScale(scale, scale);
}

const int Enemy::GetPoints() const
{
	return points;
}

void Enemy::Move(const sf::Vector2f& target, const float dt)
{
	float distance = util::Distance(target, GetCenterPosition());
	sf::Vector2f target_dir = util::Normalize(target - GetCenterPosition());
	sf::Vector2f dir;

	if (distance > distanceThreshold) {
		dir = target_dir;
	}
	else if (distance > distanceThreshold * 0.8) {
		dir = sf::Vector2f(0, 0);
	}
	else {
		dir = -target_dir;
	}

	velocity += dir * acceleration * dt;
}

void Enemy::Shoot(std::list<Bullet>& bullets, sf::Vector2f target)
{
	if (shootTimer.Ready()) {
		sf::Vector2f start_pos = GetCenterPosition();
		sf::Vector2f direction = util::Normalize(target - start_pos);
		sf::Color color = sf::Color(255, 0, 0);
		int damage = 1;
		float radius = 30;
		float speed = 1000;
		float distance = 5000;

		bullets.emplace_back(start_pos, direction, color, damage, radius, speed, distance);
	}
}



void Enemy::Update(const sf::Vector2f& target, const float dt)
{
	invincibilityTimer.Update(dt);
	shootTimer.Update(dt);

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
