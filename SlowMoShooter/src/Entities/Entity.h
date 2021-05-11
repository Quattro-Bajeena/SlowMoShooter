#pragma once
#include "Utility/Utility.h"
class Entity
{
protected:
	sf::Sprite sprite;
	
	int health;
	int healthMax;
	bool dead;

	bool invincibility;
	float invincibilityTimer;
	float invincibilityTimerMax;

	//Movement
	float acceleration;
	float deceleration;
	float maxVelocity;
	

	sf::Vector2f velocity;
	sf::Vector2i inputDir;

	//sf::Vector2f position;
	//sf::FloatRect hitBox;

public:
	Entity();
	virtual ~Entity();

	//Setters
	void SetHealth(int new_health);

	//Accesors
	virtual const sf::Vector2f GetPosition() const;
	virtual const sf::Vector2f GetCenterPosition() const;
	virtual const sf::Vector2i GetGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect GetGlobalBounds() const;
	//virtual const sf::FloatRect GetNextPositionBounds(const float& dt) const;

	const bool CheckCollision(sf::FloatRect object) const;
	const bool CheckContain(sf::FloatRect object) const;
	const float GetDistance(const sf::Vector2f& position) const;
	sf::Vector2f CalculateDir(const sf::Vector2f& position);

	//Gameplay accesors
	const int GetHealth() const;
	const int GetMaxHealth() const;
	const bool IsDead() const;
	const bool IsInvincible() const;

	//Mopdifers
	virtual void Die();
	virtual void LooseHealthInv(int damage);
	virtual void LooseHealth(int damage);
	virtual void Move(const sf::Vector2i dir, const float dt);


	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void StopVelocity(bool x, bool y);

	virtual void UpdateMovement(const float dt);
	virtual void Update(const float dt) = 0;
	virtual void Render(sf::RenderTarget& target) const = 0;
};

