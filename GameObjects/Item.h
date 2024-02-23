#pragma once
#include "SpriteGo.h"

class Player;

class Item :
    public SpriteGo
{
public:

	enum class Types
	{
		AMMO,
		HEAL,
	};
protected:

	Types type = Types::HEAL;
	Player* player;
	
	bool isPickUp = false;

public:

	Item(const std::string& name = "Item");
	~Item() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	static Item* Create(Types type);
};

