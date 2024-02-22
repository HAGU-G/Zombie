#pragma once
#include "SpriteGo.h"

class Player;

class Bullet : public GameObject
{
protected:
    sf::Vector2f direction;
    sf::RectangleShape shape;
    float speed;
    int damage;

    bool isHit = false;

public:
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

