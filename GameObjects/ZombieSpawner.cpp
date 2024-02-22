#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:GameObject(name)
{
}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();
}

void ZombieSpawner::Reset()
{
	GameObject::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Chaser);

	interval = 1.f; //аж╠Б
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;
}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);
	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
			Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
			dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->AddZombie(zombieType)->SetPosition(pos);

		}
	}
}
