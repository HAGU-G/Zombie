#pragma once
#include "Scene.h"
#include "Zombie.h"


class ZombieSpawner;
class Player;
class SceneGame : public Scene
{
protected:
	Player* player;
	std::vector<ZombieSpawner*> spawners;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void PostUpdate(float dt);

	void Draw(sf::RenderWindow& window) override;

	inline Player* GetPlayer() { return player; }

	std::list<Zombie*> zombieObjects;
	Zombie* AddZombie(Zombie::Types zombieType);
};

