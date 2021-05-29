#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(sf::Vector2f pos, float radius, sf::Texture& texture)
	:texture(texture), radius(radius)
{
	active = true;
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.scale(0.5, 0.5);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	defaultBounds = sprite.getGlobalBounds();
}

void Arrow::Deactivate()
{
	active = false;
}

void Arrow::Update(sf::Vector2f playerPos, sf::Vector2f target)
{
	if (active == false)
		return;

	sf::Vector2f direction = util::Normalize(target - playerPos);
	sf::Vector2f position = (playerPos + direction * radius);
	float rotation = (std::atan2(direction.y, direction.x) / M_PI) * 180;
	sprite.setPosition(position);
	sprite.setRotation(rotation);
}

void Arrow::Render(sf::RenderTarget& target) const
{
	if(active)
		target.draw(sprite);
}
