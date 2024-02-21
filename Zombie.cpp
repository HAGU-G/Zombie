#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
}

Zombie* Zombie::Create(Types zombieType, Player* player)
{
	Zombie* zombie = new Zombie();
	zombie->player = player;
	zombie->type = zombieType;
	zombie->SetPosition(Utils::RandomOnUnitCircle() * Utils::RandomRange(500.f, 2000.f) + player->GetPosition());



	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 30;
		zombie->speed = 50;
		break;
	default:
		break;
	}

	return zombie;
}

void Zombie::Init()
{
	SpriteGo::Init();

	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	//플레이어 할당 : Create에서 했다.
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	//플레이어에게 이동
	if (distanceToPlayer > speed * dt)
		SetPosition(GetPosition() + Utils::GetNormalize(player->GetPosition() - GetPosition()) * speed * dt);
	//좀비끼리 충돌 검사
	for (auto ptr : dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->zombieObjects)
	{
		if (ptr == this)
			continue;
		float distance = Utils::Distance(ptr->GetPosition(), GetPosition());
		float minDistance = sprite.getLocalBounds().width / 3 + ptr->GetLocalBounds().width / 3;
		if (distance < minDistance && distanceToPlayer > ptr->GetDistanceToPlayer())
		{
			SetPosition(GetPosition() - (minDistance - distance) * Utils::GetNormalize(ptr->GetPosition() - GetPosition()));
		}
	}

	rotation = Utils::Angle(player->GetPosition() - GetPosition());
	SetRotation(rotation);
	distanceToPlayer = Utils::Distance(player->GetPosition(), GetPosition());
	if (distanceToPlayer < sprite.getLocalBounds().width / 3 + player->GetLocalBounds().width / 3)
	{
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->DeleteGo(this);
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
