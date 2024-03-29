#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "Bullet.h"
#include "Crosshair.h"
#include "Item.h"
#include "DebugString.h"
#include "UIHUD.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	Release();

	//UI
	crosshair = dynamic_cast<Crosshair*>(AddGo(new Crosshair(), Scene::Ui));

	hud = dynamic_cast<UIHUD*>(AddGo(new UIHUD(), Scene::Ui));

	AddGo(new DebugString(), Scene::Ui);

	//기존HP
	//healthBar.setSize({ (float)player->maxHp,40 });
	//healthBar.setFillColor(sf::Color::Red);
	//Utils::SetOrigin(healthBar, Origins::BC);
	//healthBar.setPosition({ FRAMEWORK.GetWindow().mapPixelToCoords(FRAMEWORK.GetWindowSize(),uiView).x * 0.5f
	//	, FRAMEWORK.GetWindow().mapPixelToCoords(FRAMEWORK.GetWindowSize(), uiView).y * 0.95f });


	//배경
	AddGo(new TileMap("Background"));

	//좀비 스포너
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());
	for (auto s : spawners)
	{
		if (s->name == "ItemSpawner")
		{
			s->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f });
		}
		else if (s->name == "ZombieSpawner")
		{
			s->SetPosition({ Utils::RandomRange(0.f,(float)FRAMEWORK.GetWindowSize().x),Utils::RandomRange(0.f,(float)FRAMEWORK.GetWindowSize().y) });
		}
		AddGo(s);
	}

	//플레이어
	player = new Player("Player");
	AddGo(player);

	Scene::Init();

	hud->SetScore(score);
	hud->SetHiScore(hiScore);
	hud->SetAmmo(0, 0);
	hud->SetWave(wave);
	hud->SetZombieCount(zombieObjects.size());
}

void SceneGame::Release()
{
	Scene::Release();
	for (auto ptr : zombieObjects)
	{
		ptr = nullptr;
	}
	zombieObjects.clear();
	for (auto ptr : spawners)
	{
		ptr = nullptr;
	}
	spawners.clear();
	for (auto ptr : bullets)
	{
		ptr = nullptr;
	}
	bullets.clear();
	player = nullptr;
	score = hiScore = 0;
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	Scene::Enter();

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
	//tileMap->SetScale({ 2.f,2.f });
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
	//findGoAll("Zombie",zombieList,Layer::World); FixedUpdate에서도 설정

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
		CreateItem(Item::Types::HEAL)->SetPosition({ 500,500 });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		CreateZombie(Zombie::Types(rand() % (int)Zombie::Types::Count));
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




	PostUpdate(dt);
}

void SceneGame::PostUpdate(float dt)
{
	//zombieObjects.sort();



}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

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
	hud->SetZombieCount(zombieObjects.size());
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
	BulletCollision(dt);
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

Item* SceneGame::CreateItem(Item::Types itemType)
{
	Item* i = Item::Create(Item::Types::HEAL);
	i->Init();
	i->Reset();
	AddGo(i);
	return i;
}

void SceneGame::BulletCollision(float dt)
{
	for (auto zombie : zombieObjects)
	{
		if (zombie->isDead)
			continue;
		for (auto bullet : bullets)
		{
			if (!zombie->isDead && !bullet->isHit && Utils::IsCollideWithLineSegment(zombie->GetPosition(), bullet->GetPosition(), bullet->prePos, zombie->GetGlobalBounds().width / 3.f))
			{
				bullet->Hit();
				score += zombie->Damaged(bullet->damage);
				hud->SetScore(score);
				hud->SetHiScore(hiScore = std::max(score, hiScore));
				zombie->SetPosition(zombie->GetPosition() + zombie->GetDirection() * -1.f * 5.f);
			}
		}
	}
}

//sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
//{
//	sf::FloatRect rect = tileMap->GetGlobalBounds();
//	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
//
//	return Utils::Clamp();
//}
