#pragma once
#include "Scene.h"
#include "Zombie.h"
#include "Item.h"


class ZombieSpawner;
class Player;
class Bullet;

class SceneGame : public Scene
{
protected:
	Player* player;
	std::vector<ZombieSpawner*> spawners;

	int score = 0;
	sf::RectangleShape healthBar;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	bool doReset = false;

	void BulletCollision();

public:
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);



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
	inline const std::pair<sf::Vector2f, sf::Vector2f>& GetBoundary() const { return boundary; }

	std::list<Zombie*> zombieObjects;
	Zombie* CreateZombie(Zombie::Types zombieType);

	std::list<Bullet*> bullets;
	Bullet* CreateBullet(Player* player);

	Item* CreateItem(Item::Types itemType);

};

