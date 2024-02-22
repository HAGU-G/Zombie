#pragma once
#include "GameObject.h"
class HealthBar : public GameObject
{
protected:
	sf::RectangleShape shape;

public:
	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

