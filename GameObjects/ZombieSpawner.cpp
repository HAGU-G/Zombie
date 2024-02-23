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

	interval = 2000.f; //аж╠Б
	spawnCount = 1;
	radius = 250.f;
	timer = 2000.f;
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();

}

void ZombieSpawner::Update(float dt)
{


	GameObject::Update(dt);
	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
			Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];

			if (pos.x < boundary.first.x)
				Utils::ElasticCollision(pos.x, boundary.first.x, 0.f);
			if (pos.x > boundary.second.x)
				Utils::ElasticCollision(pos.x, boundary.second.x, 0.f);
			if (pos.y < boundary.first.y)
				Utils::ElasticCollision(pos.y, boundary.first.y, 0.f);
			if (pos.y > boundary.second.y)
				Utils::ElasticCollision(pos.y, boundary.second.y, 0.f);

			dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->CreateZombie(zombieType)->SetPosition(pos);

		}
	}
}
