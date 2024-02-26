#pragma once
#include "SpriteGo.h"
class Player;

class Item2: public SpriteGo
{
public:
	enum class Types
	{
		NONE = -1,
		AMMO,
		HEALTH,


		COUNT,
	};
protected:
	Types type;
	int value;

	Player* player;

public:
	Item2(const std::string& name = "");
	~Item2() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;


	static Item2* Create(Types t, int v);
	Types GetType() const { return type; }
	int GetValue()const { return value; }
};