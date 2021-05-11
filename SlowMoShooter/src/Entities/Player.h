#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    sf::Texture texture;
    float maxVelocityDefault;
    float dashVelocity;

    bool dashing;
    

public:
    Player();
    ~Player();


    void LooseHealth(int damage) override;
    void LooseHealthInv(int damage) override;

    void Move(const sf::Vector2i dir, const float dt) override;
    void StartDash();
    void EndDash();

    void Update(const float dt) override;
    void Render(sf::RenderTarget& target) const override;

};

