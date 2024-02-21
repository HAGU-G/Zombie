#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
	zombieObjects.clear();
}

void SceneGame::Enter()
{
	Scene::Enter();

	srand(time(NULL));

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);



	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	player->SetPosition(centerPos);
	tileMap->SetPosition(centerPos);
	tileMap->SetOrigin(Origins::MC);
	//tileMap->SetRotation(0);
	tileMap->UpdateTransform();

	worldView.setCenter(player->GetPosition());

}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	
	sf::Vector2f speed = player->GetPosition() - worldView.getCenter();
	worldView.move(speed * dt * 2.f);
	if (Utils::Distance(player->GetPosition(),worldView.getCenter()) <= 1.f && InputMgr::GetAxis(Axis::Horizontal)==0.f&& InputMgr::GetAxis(Axis::Vertical) == 0.f)
		worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		AddZombie();
	}
	if (InputMgr::GetKey(sf::Keyboard::Delete))
	{
		for (size_t i = 0; i < zombieObjects.size();i++)
		{
			Zombie* temp = zombieObjects.front();
			RemoveGo(temp);
			zombieObjects.pop_front();
			delete temp;
		}

	}
	if (InputMgr::GetKey(sf::Keyboard::BackSpace))
	{
		for (size_t i = 0; i < zombieObjects.size(); i++)
		{
			Zombie* temp = zombieObjects.front();
			RemoveGo(temp);
			zombieObjects.pop_front();
			delete temp;
		}

	}

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


Zombie* SceneGame::AddZombie()
{
	Zombie* z = Zombie::Create(Zombie::Types(rand() % 3), player);
	z->Init();
	z->Reset();
	AddGo(z);
	zombieObjects.push_back(z);
	return z;
}