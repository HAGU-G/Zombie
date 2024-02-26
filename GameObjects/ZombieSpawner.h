#pragma once
#include "Spawner.h"
#include "Zombie.h"

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;


public:
	ZombieSpawner(const std::string& name = "ZombieSpawner");
	~ZombieSpawner()override =default;

	void Reset() override;

	GameObject* Create() override;
};