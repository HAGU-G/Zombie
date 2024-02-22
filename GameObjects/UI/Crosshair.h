#pragma once
#include "SpriteGo.h"
class Crosshair : public SpriteGo
{
public:
	Crosshair(const std::string& name = "crosshair");
	~Crosshair() = default;

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

