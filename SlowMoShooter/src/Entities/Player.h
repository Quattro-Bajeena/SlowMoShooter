#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    sf::Texture texture;

public:
    Player();
    ~Player();


    void LooseHealth(int damage) override;
    void LooseHealthInv(int damage) override;


    void Update(const float dt) override;
    void Render(sf::RenderTarget& target) const override;

};

