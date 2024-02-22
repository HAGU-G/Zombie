#pragma once
#include "SpriteGo.h"

class Player;

class Bullet : public GameObject
{
protected:
    sf::Vector2f direction;
    float speed;
    int damage;
    float displacement = 0.f; //움직인 거리


public:
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
    
    void Hit(sf::Vector2f hitedObjectPos);

    static Bullet* Create(Player* player);
};

