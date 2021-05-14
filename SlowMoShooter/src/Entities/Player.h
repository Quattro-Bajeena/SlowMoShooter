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
    
    float dashTimer;
    float dashTimerMax;
    float dashRechargeTimer;
    float dashRechargeTimeMax;

public:
    Player();
    ~Player();


    void LooseHealth(int damage) override;
    void LooseHealthInv(int damage) override;

    void Move(const sf::Vector2i dir, const float dt);
    void StartDash();
    void EndDash();

    void Shoot(std::list<Bullet>& bullets, sf::Vector2f target) override;

    void Update(const float dt);
    void Render(sf::RenderTarget& target) const override;

};

