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
    
    Timer dashTimer;
    Timer dashRechargeTimer;

    Timer shootTimer;

    //GUN
    sf::Texture gunTexture;
    sf::Sprite gunSprt;
    sf::FloatRect gunDefaultBounds;
    sf::Vector2f gunTip;
    sf::Vector2f gunDirection;
    float gunDistance;

public:
    Player(sf::Vector2f pos);
    ~Player();


    void LooseHealth(int damage) override;
    void LooseHealthInv(int damage) override;

    void Move(const sf::Vector2i dir, const float dt);
    void StartDash();
    void EndDash();

    void Shoot(std::list<Bullet>& bullets, sf::Vector2f target) override;
    void UpdateGunPos(sf::Vector2f mouse_pos);

    void Update(sf::Vector2f mouse_pos, const float dt);
    void Render(sf::RenderTarget& target) const override;

};

