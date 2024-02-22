#pragma once
#include "SpriteGo.h"
class EffectBlood :
    public SpriteGo
{
protected:
	float timer = 5.f;
	bool del = false;
public:
	EffectBlood(sf::Vector2f pos, const std::string& name = "Blood");
	~EffectBlood()override = default;


	void Init() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

