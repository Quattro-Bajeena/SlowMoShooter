#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir,sf::Color color,
	int damage, float radius, float max_speed, float max_distance)
	:direction(dir), maxSpeed(max_speed), maxDistance(max_distance), damage(damage), distanceTraveled(0)
{
	shape.setPosition(startPos);
	shape.setRadius(radius);
	shape.setFillColor(color);
	currentVelocity = direction * maxSpeed;
	
}

void Bullet::Update(const float dt)
{
	distanceTraveled += maxSpeed * dt;
	shape.move(currentVelocity * dt);
}

bool Bullet::CheckCollision(sf::FloatRect object) const
{
	return object.intersects(shape.getGlobalBounds());
}

bool Bullet::DistanceLimit(const sf::Vector2f& position) const
{
	sf::Vector2f vector = position - shape.getPosition();
	float distance = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	return distance > maxDistance;
}

bool Bullet::TraveledMaxDistance() const
{
	return distanceTraveled > maxDistance;
}

const sf::FloatRect Bullet::GetBounds() const
{
	return shape.getGlobalBounds();
}

const int Bullet::GetDamage() const
{
	return damage;
}

void Bullet::Render(sf::RenderTarget& target) const
{
	target.draw(shape);
}
