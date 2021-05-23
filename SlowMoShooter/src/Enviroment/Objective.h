#pragma once
class Objective
{
private:
	sf::Sprite sprite;
	bool activated;
	float threshold;

	sf::Texture& deactivatedTexture;
	sf::Texture& activatedTexture;

public:
	Objective(float x, float y, float threshold, sf::Texture& deactivated_texture, sf::Texture& activated_texture);

	sf::Vector2f GetPosition() const;
	bool Activate(sf::Vector2f pos);
	bool IsActivated() const;

	void Render(sf::RenderTarget& target) const;
};

