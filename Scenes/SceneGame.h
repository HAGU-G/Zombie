#pragma once
#include "Scene.h"
#include "Zombie.h"

class Player;
class SceneGame : public Scene
{
protected:
	Player* player;
	std::deque<GameObject*> deleteDeque;

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
	void DeleteGo(GameObject* obj);

	std::list<Zombie*> zombieObjects;
	Zombie* AddZombie();
};

