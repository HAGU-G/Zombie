#pragma once
#include "Scene.h"
#include "Zombie.h"
#include "Item.h"


class Player;
class Bullet;
class TileMap;
class Spawner;
class UIHUD;
class Crosshair;

class SceneGame : public Scene
{
protected:
	Player* player;
	UIHUD* hud;

	std::vector<Spawner*> spawners;

	int score = 0;
	int hiScore = 0;
	int wave = 0;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	bool doReset = false;

	void BulletCollision(float dt);

public:
	//sf::Vector2f ClampByTileMap(const sf::Vector2f& point);
	Crosshair* crosshair;


	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void PostUpdate(float dt);
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	inline Player* GetPlayer() { return player; }
	inline const std::pair<sf::Vector2f, sf::Vector2f>& GetBoundary() const { return boundary; }

	Zombie* CreateZombie(Zombie::Types zombieType);

	std::list<Bullet*> bullets;
	Bullet* CreateBullet(Player* player);

	Item* CreateItem(Item::Types itemType);



	std::list<Zombie*> zombieObjects;


};

