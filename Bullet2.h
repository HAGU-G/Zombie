#pragma once
#include "SpriteGo.h"

class SceneGame;


class Bullet2 : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;

	SceneGame* sceneGame;


public:
	Bullet2(const std::string& name="bullet2");
	~Bullet2() override = default;

	void Fire(const sf::Vector2f& dir, float s);


	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

