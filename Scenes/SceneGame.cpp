#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "Bullet.h"
#include "Crosshair.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	//배경
	AddGo(new TileMap("Background"));

	//크로스헤어
	AddGo(new Crosshair(), Scene::Ui);

	//좀비 스포너
	//spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	//플레이어
	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
	zombieObjects.clear();
	spawners.clear();
	bullets.clear();
	player = nullptr;
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
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
	//tileMap->SetRotation(45);
	tileMap->UpdateTransform();
	boundary = tileMap->GetBoundary();

	worldView.setCenter(player->GetPosition());

}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));

	sf::Vector2f speed = player->GetPosition() - worldView.getCenter();
	worldView.move(speed * dt * 2.f);
	if (Utils::Distance(player->GetPosition(), worldView.getCenter()) <= 1.f && InputMgr::GetAxis(Axis::Horizontal) == 0.f && InputMgr::GetAxis(Axis::Vertical) == 0.f)
		worldView.setCenter(player->GetPosition());

	//추가
	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		CreateZombie(Zombie::Types(rand() % (int)Zombie::Types::Count));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		CreateZombie(Zombie::Types(rand() % (int)Zombie::Types::Count));
		tileMap->sortLayer = 50;
		ReSoltGo(tileMap);
	}
	//전부 제거
	if (InputMgr::GetKeyDown(sf::Keyboard::Delete))
	{
		while (zombieObjects.size() > 0)
		{
			Zombie* temp = zombieObjects.front();
			RemoveGo(temp);
			zombieObjects.pop_front();
			delete temp;
		}
	}
	//하나씩 랜덤하게 제거
	if (InputMgr::GetKey(sf::Keyboard::BackSpace))
	{
		size_t siz = zombieObjects.size();
		if (siz != 0)
		{
			int t = rand() % siz;
			auto it = zombieObjects.begin();
			for (int i = 0; i < t; i++)
			{
				it++;
			}
			RemoveGo(*it);
			Zombie* z = *it;
			zombieObjects.remove(*it);
			delete z;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		doReset = true;
	}

	BulletCollision();

	PostUpdate(dt);
}

void SceneGame::PostUpdate(float dt)
{
	//오브젝트 삭제 (delete)
	while (deleteDeque.size() > 0)
	{
		//필요한 정보를 미리 가져온다.
		GameObject* temp = deleteDeque.front();
		int tag = temp->GetTag();

		//삭제 시작
		RemoveGo(temp);
		deleteDeque.pop_front(); 
		if (tag == 0)
			zombieObjects.remove(dynamic_cast<Zombie*>(temp));
		else if (tag == 1)
			bullets.remove(dynamic_cast<Bullet*>(temp));
		delete temp;
	}
	if (doReset)
	{
		doReset = false;
		Release();
		Init();
		Enter();
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


Zombie* SceneGame::CreateZombie(Zombie::Types zombieType)
{
	Zombie* z = Zombie::Create(zombieType);
	z->Init();
	z->Reset();
	z->SetPlayer(player);
	AddGo(z);
	zombieObjects.push_back(z);
	return z;
}

Bullet* SceneGame::CreateBullet(Player* player)
{
	Bullet* b = Bullet::Create(player);
	b->Init();
	b->Reset();
	AddGo(b);
	bullets.push_back(b);
	return b;
}



void SceneGame::BulletCollision()
{
	for (auto zombie : zombieObjects)
	{
		if (!zombie->isDead)
		{
			for (auto bullet : bullets)
			{
				if (!zombie->isDead && !bullet->isHit && Utils::IsCollideWithLineSegment(zombie->GetPosition(), bullet->GetPosition(), bullet->prePos, zombie->GetGlobalBounds().width * 4.5f / 10.f))
				{
					zombie->isDead = true;
					bullet->Hit(zombie->GetPosition());
					DeleteGo(zombie);
				}
			}
		}
	}

}