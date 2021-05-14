#pragma once
#include "Entities/Entity.h"

class Enemy :
    public Entity
{
protected:
	std::vector<Bullet> bullets;

	//enemyType type;
	//enemyState state;

	//float size;
	int points;
	int damage;
	//bool canShoot;
	float distanceThreshold;

	float shootTimer;
	float shootTimerMax;

	sf::Text text;
	//Functions
	//void updateState();
	//void updateColor();

public:
	Enemy(sf::Vector2f position, sf::Texture& texture);

	//Accesors
	const int GetPoints()const;
	//const enemyType getType() const;

	//Function
	void Move(const sf::Vector2f& target, const float dt);
	void Shoot(std::list<Bullet>& bullets, sf::Vector2f target) override;

	void Update(const sf::Vector2f& target, const float& dt);
	void Render(sf::RenderTarget& target) const override;
};

