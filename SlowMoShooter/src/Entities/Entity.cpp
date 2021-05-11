#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	invincibility = false;
	invincibilityTimer = 0;
	invincibilityTimerMax = 0.5;

	dead = false;
	velocity = sf::Vector2f();

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
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
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
	if (this->invincibility == false) {
		this->health -= damage;
		this->invincibility = true;
		this->invincibilityTimer = 0.f;
	}
}

void Entity::LooseHealth(int damage)
{
	if (invincibility == false) {
		health -= damage;
	}
}

void Entity::Move(const sf::Vector2f offset, const float dt)
{
	sprite.move( maxVelocity * offset * dt);
}

void Entity::SetPosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

void Entity::StopVelocity(bool x, bool y)
{
	if (x)
		velocity.x = 0;
	if (y)
		velocity.y = 0;
}

