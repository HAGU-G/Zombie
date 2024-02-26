#include "pch.h"
#include "Item2.h"
#include "Player.h"

Item2::Item2(const std::string& name)
	:SpriteGo(name), type(Types::NONE), value(0), player(nullptr)
{
}

void Item2::Init()
{
	SpriteGo::Init();
}

void Item2::Release()
{
	SpriteGo::Release();
}

void Item2::Reset()
{
	SpriteGo::Reset();
	SetOrigin(Origins::MC);
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void Item2::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Item2::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Item2::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

	if (player == nullptr)
		return;
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);
		player->onItem(this);
	}
}

void Item2::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Item2* Item2::Create(Types t, int v)
{
	Item2* newItem = new Item2();
	newItem->type = t;
	newItem->value = v;

	switch (newItem->type)
	{
	case Types::AMMO:
		newItem->textureId = "graphics/ammo_pickup.png";
		break;
	case Types::HEALTH:
		newItem->textureId = "graphics/health_pickup.png";
		break;
	}


	newItem->Init();
	newItem->Reset();
	return newItem;
}
