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
	static Zombie* Create(Types zombieType);
	static const int TotalTypes = (const int)Types::Count;


protected:
	Types type;
	
	int maxHp = 1;
	float speed = 1;

	int currentHp = 1;
	int aktDamage = 1;

	Player* player;
	float distanceToPlayer;
	sf::Vector2f direction;

	Zombie(const std::string& name="");


public:
	~Zombie() = default;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	inline float GetDistanceToPlayer() const { return distanceToPlayer; }

	inline void SetPlayer(Player* p) { player = p; }

};

