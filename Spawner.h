#pragma once
#include "GameObject.h"

class SceneGame;


class Spawner : public GameObject
{
protected:
	float interval = 1.f; //аж╠Б
	int spawnCount = 1;
	float radius = 250.f;

	float timer = 0.f;

	SceneGame* sceneGame;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

public:
	Spawner(const std::string& name = "");
	~Spawner()override = default;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);

	virtual GameObject* Create() = 0;

	void SetInterval(float v) { interval = v; }
	void SetSpawnCount(int v) { spawnCount = v; }
	void SetRadius(float v) { radius = v; }
	void SetTimer(float v) { timer = v; }

};