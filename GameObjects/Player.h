#pragma once
#include "SpriteGo.h"

class TileMap;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction;
	sf::Vector2f look = { 1.f, 0.f };
	std::pair<sf::Vector2f, sf::Vector2f> boundary;
	
	float shotInterval = 0.f;
	float shotTimer = 0.f;
	bool isFiring = false;

	float speed = 600.f;

	TileMap* tileMap;
	std::string textureId = "graphics/player.png";

public:
	int maxHp = 100;
	int hp = 100;
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

