#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "Bullet.h"

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
		zombie->maxHp = zombie->hp = 300;
		zombie->maxSpeed = zombie->speed = 30;
		zombie->atkDamage = 70;
		zombie->atkInterval = zombie->atkTimer = 2.f;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = zombie->hp = 100;
		zombie->speed = zombie->maxSpeed = 75;
		zombie->atkDamage = 10;
		zombie->atkInterval = zombie->atkTimer = 0.5f;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = zombie->hp = 30;
		zombie->speed = 0;
		zombie->maxSpeed = 100;
		zombie->atkDamage = 100;
		zombie->atkInterval = zombie->atkTimer = 3.f;
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
	//�÷��̾� �Ҵ� : Create���� �ߴ�.
}

void Zombie::Update(float dt)
{
	atkTimer += dt;
	SpriteGo::Update(dt);

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	if (type == Types::Crawler)
	{
		speed += maxSpeed * 2 * dt;
		if (speed > maxSpeed)
			speed = 0;
	}

	//�÷��̾�� �̵�
	if (distanceToPlayer > sprite.getGlobalBounds().width / 3)
		//SetPosition(GetPosition() + Utils::GetNormalize(player->GetPosition() - GetPosition()) * speed * dt);
		Translate(direction * speed * dt);

	//�浹 �˻�
	Collision(dt);

	//�÷��̾� ����
	if (atkTimer >= atkInterval && distanceToPlayer < sprite.getGlobalBounds().width / 3)
	{
		player->Damaged(atkDamage);
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::Collision(float dt)
{
	//����
	for (auto ptr : dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->zombieObjects)
	{
		if (ptr == this)
			continue;
		sf::Vector2f dz = Utils::GetNormalize(ptr->GetPosition() - position); //�ٸ� ������� ����
		float distance = Utils::Distance(ptr->GetPosition(), position); //�ٸ� ������� �Ÿ�
		float minDistance = sprite.getGlobalBounds().width / 3.f + ptr->GetLocalBounds().width / 3.f; //�ּ� �Ÿ�
		if (distance < minDistance)
		{
			SetPosition(position - dz * speed * 2.f * dt);
		}
	}

	//������
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

