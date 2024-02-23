#pragma once
#include "SpriteGo.h"

class Player;

class Bullet : public GameObject
{
protected:
    sf::Vector2f direction;
    float speed;
    float displacement = 0.f; //움직인 거리
    float isStuckInWall = false;


public:
    int damage;
    bool isHit = false;
    sf::Vector2f prePos;
    sf::RectangleShape shape;

    Bullet(const sf::Vector2f& position, const std::string& name = "bullet");
    ~Bullet() = default;


    void Init()override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    
    void Hit();

    static Bullet* Create(Player* player);
};

