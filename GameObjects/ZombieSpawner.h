#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f; //аж╠Б
	int spawnCount = 1;
	float radius = 250.f;

	float timer = 0.f;

	std::pair<sf::Vector2f, sf::Vector2f> boundary;


public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner()override =default;

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
};