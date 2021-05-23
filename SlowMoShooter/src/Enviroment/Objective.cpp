#include "stdafx.h"
#include "Objective.h"

Objective::Objective(float x, float y, float threshold, sf::Texture& deactivated_texture, sf::Texture& activated_texture)
	:deactivatedTexture(deactivated_texture), activatedTexture(activated_texture), threshold(threshold)
{
	sprite.setTexture(deactivatedTexture);
	sprite.setPosition(x, y);
	activated = false;
	sprite.scale(1.2, 1.2);
}

sf::Vector2f Objective::GetPosition() const
{
	return sf::Vector2f(
		sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
		sprite.getPosition().y + sprite.getGlobalBounds().height / 2
	);
}

bool Objective::Activate(sf::Vector2f pos)
{

	if (activated == false && util::Distance(pos, GetPosition()) <= threshold) {
		activated = true;
		sprite.setTexture(activatedTexture);
		return true;
	}
	else return false;
}

bool Objective::IsActivated() const
{
	return activated;
}

void Objective::Render(sf::RenderTarget& target) const
{
	target.draw(sprite);
}
