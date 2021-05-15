#pragma once
#include "Utility/utility.h"
class Bullet
{
private:
	float distanceTraveled;
	float maxDistance;
	
	sf::CircleShape shape;
	float maxSpeed;
	int damage;
	sf::Vector2f direction;
	sf::Vector2f currentVelocity;
	bool hitSomething;


public:
	Bullet(sf::Vector2f startPos, sf::Vector2f dir,
		sf::Color color, int damage, float radius,
		float max_speed, float max_distance);

	void Update(const float dt);
	bool CheckCollision(sf::FloatRect object) const;
	bool DistanceLimit(const sf::Vector2f& position) const;

	bool TraveledMaxDistance() const;
	void RegisterHit();

	//Accesors
	const sf::FloatRect GetBounds() const;
	const int GetDamage() const;
	bool ToBeRemoved() const;

	void Render(sf::RenderTarget& target) const;
};

