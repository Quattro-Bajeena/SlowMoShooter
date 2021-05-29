#pragma once
class Arrow
{
private:
	sf::Sprite sprite;
	sf::Texture& texture;
	float radius;
	sf::FloatRect defaultBounds;
	bool active;

public:
	Arrow(sf::Vector2f pos, float radius, sf::Texture& texture);

	void Deactivate();
	void Update(sf::Vector2f playerPos, sf::Vector2f target);
	void Render(sf::RenderTarget& target) const;
};

