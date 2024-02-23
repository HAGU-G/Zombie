#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "Bullet.h"
#include <EffectBlood.h>

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
	tag = 0;
	sortLayer = 10;
}

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie();
	zombie->type = zombieType;


	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = zombie->hp = 141;
		zombie->maxSpeed = zombie->speed = 30;
		zombie->atkDamage = 70;
		zombie->atkInterval = zombie->atkTimer = 1.f;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = zombie->hp = 69;
		zombie->speed = zombie->maxSpeed = 75;
		zombie->atkDamage = 10;
		zombie->atkInterval = zombie->atkTimer = 0.5f;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = zombie->hp = 103;
		zombie->speed = 0;
		zombie->maxSpeed = 200;
		zombie->atkDamage = 99;
		zombie->atkInterval = zombie->atkTimer = 2.f;
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
	atkTimer += dt;
	SpriteGo::Update(dt);

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	//기어다니는 친구
	if (type == Types::Crawler)
	{
		speed += (speed * 5.f + 1.f) * dt;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}

	//플레이어에게 이동
	if (distanceToPlayer > sprite.getGlobalBounds().width * 3.8f / 10.f)
	{
		//SetPosition(GetPosition() + Utils::GetNormalize(player->GetPosition() - GetPosition()) * speed * dt);
		Translate(direction * speed * dt);
		if (type == Types::Crawler && speed >= maxSpeed)
		{
			speed = 0.f;
			atkTimer = 0.f;
		}
	}

	//충돌 검사
	Collision(dt);

	direction = player->GetPosition() - position;

	if (atkTimer >=atkInterval && distanceToPlayer <= sprite.getGlobalBounds().width * 3.8f / 10.f)
	{
		player->Damaged(atkDamage);
		atkTimer = 0.f;
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

//충돌
void Zombie::Collision(float dt)
{
	//좀비
	for (auto ptr : dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->zombieObjects)
	{
		if (ptr == this)
			continue;
		sf::Vector2f dz = Utils::GetNormalize(ptr->GetPosition() - position); //다른 좀비로의 방향
		float distance = Utils::Distance(ptr->GetPosition(), position); //다른 좀비와의 거리
		float minDistance = sprite.getGlobalBounds().width / 3.f + ptr->GetGlobalBounds().width / 3.f; //최소 거리
		if (distance < minDistance)
		{
			SetPosition(position - dz * speed * 2.f * dt);
		}
	}

	//윈도우
	sf::Vector2f tempPos = position;
	std::pair<sf::Vector2f, sf::Vector2f> boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();

	if (tempPos.x < boundary.first.x)
		Utils::ElasticCollision(tempPos.x, boundary.first.x, 0.f);
	if (tempPos.x > boundary.second.x)
		Utils::ElasticCollision(tempPos.x, boundary.second.x, 0.f);
	if (tempPos.y < boundary.first.y)
		Utils::ElasticCollision(tempPos.y, boundary.first.y, 0.f);
	if (tempPos.y > boundary.second.y)
		Utils::ElasticCollision(tempPos.y, boundary.second.y, 0.f);

	SetPosition(tempPos);
	rotation = Utils::Angle(player->GetPosition() - GetPosition());
	SetRotation(rotation);
	distanceToPlayer = Utils::Distance(player->GetPosition(), GetPosition());
}

int Zombie::Damaged(int damage)
{
	int preHp = hp;
	hp -= damage;
	if (hp <= 0 && !isDead)
	{
		hp = 0;
		isDead = true;
		SCENE_MGR.GetCurrentScene()->AddGo(new EffectBlood(this->position))->Init();
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);
	}
	return preHp - hp;
}