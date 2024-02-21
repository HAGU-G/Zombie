#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,

		Count
	};
	static Zombie* Create(Types zombieType, Player* player);
	static const int TotalTypes = (const int)Types::Count;



protected:
	Types type;
	
	int maxHp;
	float speed;

	int currenHp;
	int aktDamage;

	Player* player;

	Zombie(const std::string& name="");

public:
	~Zombie() = default;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

