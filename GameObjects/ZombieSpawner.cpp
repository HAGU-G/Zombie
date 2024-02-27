#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:Spawner(name)
{
}

void ZombieSpawner::Reset()
{

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Chaser);

	Spawner::Reset();
}

GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
	return Zombie::Create(zombieType);
}
