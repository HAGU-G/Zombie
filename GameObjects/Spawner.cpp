#include "pch.h"
#include "Spawner.h"
#include "SceneGame.h"

Spawner::Spawner(const std::string& name)
	:GameObject(name), sceneGame(nullptr)
{
}

void Spawner::Init()
{
	GameObject::Init();
}

void Spawner::Release()
{
	GameObject::Release();
}

void Spawner::Reset()
{
	GameObject::Reset();
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();

}

void Spawner::Update(float dt)
{


	GameObject::Update(dt);


	timer += dt;
	if (timer > interval && (currentCount < maxCount || maxCount == -1))
	{
		timer = 0.f;

		boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;

			if (pos.x < boundary.first.x)
				Utils::ElasticCollision(pos.x, boundary.first.x, 0.f);
			if (pos.x > boundary.second.x)
				Utils::ElasticCollision(pos.x, boundary.second.x, 0.f);
			if (pos.y < boundary.first.y)
				Utils::ElasticCollision(pos.y, boundary.first.y, 0.f);
			if (pos.y > boundary.second.y)
				Utils::ElasticCollision(pos.y, boundary.second.y, 0.f);

			GameObject* newGo = Create();
			newGo->SetPosition(pos);
			SCENE_MGR.GetCurrentScene()->AddGo(newGo);
			currentCount++;
		}
	}
}

void Spawner::Spawn(int count)
{
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	for (int j = 0; j < count; ++j)
	{
		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;

			if (pos.x < boundary.first.x)
				Utils::ElasticCollision(pos.x, boundary.first.x, 0.f);
			if (pos.x > boundary.second.x)
				Utils::ElasticCollision(pos.x, boundary.second.x, 0.f);
			if (pos.y < boundary.first.y)
				Utils::ElasticCollision(pos.y, boundary.first.y, 0.f);
			if (pos.y > boundary.second.y)
				Utils::ElasticCollision(pos.y, boundary.second.y, 0.f);

			GameObject* newGo = Create();
			newGo->SetPosition(pos);
			SCENE_MGR.GetCurrentScene()->AddGo(newGo);
		}
	}
}
