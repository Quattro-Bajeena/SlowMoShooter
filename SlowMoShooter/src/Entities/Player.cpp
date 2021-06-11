#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Vector2f pos, int max_health) :
	Entity(pos)
{
	
	health = max_health;
	healthMax = max_health;
	dead = false;
	dashing = false;

	dashTimer = Timer(0.15);
	dashRechargeTimer = Timer(1);
	invincibilityTimer = Timer(0.2);

	acceleration = 6000;
	deceleration = 7000;
	maxVelocity = maxVelocityDefault = 1500;

	dashVelocity = 7000;

	shootTimer = Timer(0.3);

	texture.loadFromFile("Assets/schizo.png");
	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(0, 0);

	gunDistance = -100;
	gunTexture.loadFromFile("Assets/gun.png");
	gunSprt.setTexture(gunTexture);
	gunDefaultBounds = gunSprt.getGlobalBounds();
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
		invincibilityTimer.Reset();
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
		invincibilityTimer.Reset();
		dashTimer.Reset();
	}
	
}

void Player::EndDash()
{
	dashing = false;
	maxVelocity = maxVelocityDefault;
	dashRechargeTimer.Reset();

	invincibility = false;
	invincibilityTimer.Ready();
}

void Player::Shoot(std::list<Bullet>& bullets, sf::Vector2f target)
{
	if (shootTimer.Ready()) {
		sf::Vector2f start_pos = gunTip;
		sf::Vector2f direction = gunDirection;
		sf::Color color = sf::Color(0, 255, 0);
		int damage = 1;
		float radius = 20;
		float speed = 5000;
		float distance = 5000;

		bullets.emplace_back(start_pos, direction, color, damage, radius, speed, distance);
	}
	
}

void Player::UpdateGunPos(sf::Vector2f mouse_pos)
{
	gunDirection = util::Normalize(mouse_pos - GetCenterPosition());
	sf::Vector2f start_pos = GetCenterPosition();

	start_pos += gunDirection * gunDistance;
	start_pos.y -= gunDefaultBounds.height / 2;

	double angle_rad = std::atan2(gunDirection.x, gunDirection.y);
	double angle = angle_rad * 180. / M_PI;

	sf::Vector2f scale(1, 1);

	gunTip = start_pos + gunDirection * gunDefaultBounds.width * 0.9f;

	if (angle < 0) {
		scale.y = -1;
		gunTip = util::RotateVector(gunTip, start_pos, -10.f);
	}
	else {
		gunTip = util::RotateVector(gunTip, start_pos, 10.f);
	}
	angle -= 90.;
	angle *= -1;

	gunSprt.setPosition(start_pos);
	gunSprt.setScale(scale);
	gunSprt.setRotation(angle);
}

void Player::Update(sf::Vector2f mouse_pos, const float dt)
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
	UpdateGunPos(mouse_pos);


}

void Player::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
	target.draw(gunSprt);
}
