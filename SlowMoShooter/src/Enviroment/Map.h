#pragma once
#include "Entities/Entity.h"
class Map
{
private:
	std::vector<sf::RectangleShape> tiles;
	int tileSize;
	std::vector<sf::Sprite> trees;

	std::vector<sf::Texture> tileTextures;
	sf::Texture treeTexture;
	sf::Vector2i mapSize;

	sf::FloatRect bounds;

public:
	Map(int width, int height, int tile_size);

	sf::FloatRect GetBounds() const;
	bool InBounds(sf::Vector2f position);
	bool Collision(sf::FloatRect rect);
	void UpdateCollision(Entity* entity, const float dt);
	void Render(sf::RenderTarget& target) const;
};

