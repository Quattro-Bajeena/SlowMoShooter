#include "stdafx.h"
#include "Entity.h"

Entity::Entity(sf::Vector2f pos)
{
	sprite.setPosition(pos);

	invincibility = false;
	invincibilityTimer = Timer(0.5);

	dead = false;
	velocity = sf::Vector2f();

	acceleration = 1000;
	deceleration = 600;
	maxVelocity = 500;

}

Entity::~Entity()
{
}

void Entity::SetHealth(int new_health)
{
	health = new_health;
}

const sf::Vector2f Entity::GetPosition() const
{
	return sprite.getPosition();
}

const sf::Vector2f Entity::GetCenterPosition() const
{
	return sf::Vector2f(
		sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
		sprite.getPosition().y + sprite.getGlobalBounds().height / 2
	);
}

const sf::Vector2i Entity::GetGridPosition(const int gridSizeI) const
{
	return sf::Vector2i(
		static_cast<int>(sprite.getPosition().x) / gridSizeI,
		static_cast<int>(sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

//const sf::FloatRect Entity::GetNextPositionBounds(const float& dt) const
//{
//	return sf::FloatRect();
//}

const bool Entity::CheckCollision(sf::FloatRect object) const
{
	return object.intersects(GetGlobalBounds());
}

const bool Entity::CheckContain(sf::FloatRect object) const
{
	return object.contains(GetCenterPosition());
}

const float Entity::GetDistance(const sf::Vector2f& position) const
{
	sf::Vector2f vector = position - GetCenterPosition();
	return std::sqrt(pow(vector.x, 2) + std::pow(vector.y, 2));;
}

sf::Vector2f Entity::CalculateDir(const sf::Vector2f& position)
{
	sf::Vector2f aimDir = (position - GetCenterPosition());
	return util::Normalize(aimDir);
}

const int Entity::GetHealth() const
{
	return health;
}

const int Entity::GetMaxHealth() const
{
	return healthMax;
}

const bool Entity::IsDead() const
{
	return dead;
}

const bool Entity::IsInvincible() const
{
	return invincibility;
}

void Entity::Die()
{
	LooseHealth(health);
}

void Entity::LooseHealthInv(int damage)
{
	if (invincibility == false) {
		health -= damage;
		invincibility = true;
		invincibilityTimer.Reset();
	}
}

void Entity::LooseHealth(int damage)
{
	if (invincibility == false) {
		health -= damage;
	}
	
}

void Entity::SetPosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

void Entity::SetPosition(const float x, const float y)
{
	SetPosition(sf::Vector2f(x, y));
}

void Entity::StopVelocity(bool x, bool y)
{
	if (x)
		velocity.x = 0;
	if (y)
		velocity.y = 0;
}

void Entity::UpdateMovement(const float dt)
{
	//Decelareate the sprite and controls the amximum velocity moves the sprite
	if (velocity.x > 0.f) { //checkh for positive x

		//deceleration x positive
		if(inputDir.x == 0)
			velocity.x -= deceleration * dt;
		if (velocity.x < 0.f)
			velocity.x = 0.f;

		//max velocity check
		if (velocity.x > maxVelocity)
			velocity.x = maxVelocity;
	}
	else if (velocity.x < 0.f) { //chechk for negative x

		//decelaretion x negative
		if (inputDir.x == 0)
			velocity.x += deceleration * dt;
		if (velocity.x > 0.f)
			velocity.x = 0.f;

		//max velocity chechk x negative
		if (velocity.x < -maxVelocity)
			velocity.x = -maxVelocity;
	}

	if (velocity.y > 0.f) { //checkh for positive y
		//deceleration y positive
		if (inputDir.y == 0)
			velocity.y -= deceleration * dt;
		if (velocity.y < 0.f)
			velocity.y = 0.f;

		//max velocity check
		if (velocity.y > maxVelocity)
			velocity.y = maxVelocity;
	}
	else if (velocity.y < 0.f) { //chechk for negative y
		//decelaretion y negative
		if (inputDir.y == 0)
			velocity.y += deceleration * dt;
		if (velocity.y > 0.f)
			velocity.y = 0.f;

		//max velocity chechk y negative
		if (velocity.y < -maxVelocity)
			velocity.y = -maxVelocity;
	}

	//std::cout << velocity.x << "|" << velocity.y << " | " << maxVelocity << "\n";

	//final move
	sprite.move(velocity * dt); //uses velocity
}

