#include "stdafx.h"
#include "Map.h"

Map::Map(int width, int height, int tile_size)
	:tileSize(tile_size), mapSize(width, height)
{
	
	treeTexture.loadFromFile("Assets/tree.png");
	tileTextures.resize(5);
	tileTextures[0].loadFromFile("Assets/tile.png");
	tileTextures[1].loadFromFile("Assets/tile1.png");
	tileTextures[2].loadFromFile("Assets/tile2.png");
	tileTextures[3].loadFromFile("Assets/tile3.png");
	tileTextures[4].loadFromFile("Assets/tile4.png");


	bounds = sf::FloatRect(0, 0, width * tileSize, height * tileSize);

	tiles.resize(height * width);
	

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			sf::RectangleShape& tile = tiles[y * width + x];
			
			tile.setPosition(x * tileSize, y * tileSize);
			tile.setTexture(&tileTextures[RNG::get().randomI(0, 4)]);
			tile.setSize(sf::Vector2f(tileSize, tileSize));

		}
	}

	int border = 5;
	for (int i = 0; i <  width/4; i++) {
		sf::Sprite tree;
		tree.scale(10, 10);
		tree.setTexture(treeTexture);
		tree.setPosition(
			RNG::get().randomF(tileSize * border, width * (tileSize- border)),
			RNG::get().randomF(tileSize *border , height * (tileSize- border))
		);
		trees.push_back(tree);
	}
}



sf::Vector2f Map::GetRandomPosition()
{
	int margin = 100;
	return sf::Vector2f(
		RNG::get().randomF(margin, bounds.height- margin),
		RNG::get().randomF(margin, bounds.width - margin)
	);
}

sf::FloatRect Map::GetBounds() const
{
	return bounds;
}

bool Map::InBounds(sf::Vector2f position)
{
	return bounds.contains(position);
}

bool Map::Collision(sf::FloatRect rect)
{
	bool collision = false;
	for (const sf::Sprite& tree : trees) {
		if (tree.getGlobalBounds().intersects(rect)) {
			collision = true;
			break;
		}
	}
	return collision;
}

void Map::UpdateCollision(Entity* entity, const float dt)
{
	//World bounds
	sf::FloatRect entityBounds = entity->GetGlobalBounds();


	for (const sf::Sprite& tree : trees) {
		sf::FloatRect treeBounds = tree.getGlobalBounds();

		if (entityBounds.intersects(treeBounds)) {
			//Bottom collisin
			if (entityBounds.top < treeBounds.top
				&& entityBounds.top + entityBounds.height < treeBounds.top + treeBounds.height
				&& entityBounds.left < treeBounds.left + treeBounds.width
				&& entityBounds.left + entityBounds.width > treeBounds.left
				)
			{
				entity->StopVelocity(false, true);
				entity->SetPosition(entityBounds.left, treeBounds.top - entityBounds.height);
			}

			//Top Collision
			else if (entityBounds.top > treeBounds.top
				&& entityBounds.top + entityBounds.height > treeBounds.top + treeBounds.height
				&& entityBounds.left < treeBounds.left + treeBounds.width
				&& entityBounds.left + entityBounds.width > treeBounds.left
				)
			{
				entity->StopVelocity(false, true);
				entity->SetPosition(entityBounds.left, treeBounds.top + treeBounds.height);
			}

			//Right collisin
			else if (entityBounds.left < treeBounds.left
				&& entityBounds.left + entityBounds.width < treeBounds.left + treeBounds.width
				&& entityBounds.top < treeBounds.top + treeBounds.height
				&& entityBounds.top + entityBounds.height > treeBounds.top
				)
			{
				entity->StopVelocity(true, false);
				entity->SetPosition(treeBounds.left - entityBounds.width, entityBounds.top);
			}

			//Left Collision
			else if (entityBounds.left > treeBounds.left
				&& entityBounds.left + entityBounds.width > treeBounds.left + treeBounds.width
				&& entityBounds.top < treeBounds.top + treeBounds.height
				&& entityBounds.top + entityBounds.height > treeBounds.top
				)
			{
				entity->StopVelocity(true, false);
				entity->SetPosition(treeBounds.left + treeBounds.width, entityBounds.top);
			}
		}

		
	}


			

		
	
}

void Map::Render(sf::RenderTarget& target) const
{
	for (const sf::RectangleShape& tile : tiles) {
		target.draw(tile);
	}

	for (const sf::Sprite& tree : trees) {
		target.draw(tree);
	}
}
