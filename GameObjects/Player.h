#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction;
	sf::Vector2f look = { 1.f, 0.f };
	sf::FloatRect boundary;
	
	int maxHp = 100;
	float damageInterval = 0.5f;

	float speed = 600.f;
	int hp = 100;


	std::string textureId = "graphics/player.png";

public:
	Player(const std::string& name);
	~Player() override = default;
	Player(const Player&) = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Damaged(int damage);
	void Shot();
};

