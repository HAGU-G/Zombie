#include "pch.h"
#include "Item.h"
#include "Player.h"
#include "SceneGame.h"

Item::Item(const std::string& name)
	:SpriteGo(name)
{
	sortLayer = 4;
	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetPlayer();
}

void Item::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetPlayer();
}

void Item::Release()
{
	SpriteGo::Release();
}

void Item::Reset()
{
	SpriteGo::Reset();
}

void Item::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isPickUp && Utils::Distance(player->GetPosition(), position) <= sprite.getGlobalBounds().width / 2.f)
	{
		isPickUp = true;
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);

		switch (type)
		{
		case Item::Types::AMMO:
			break;
		case Item::Types::HEAL:
			player->hp = std::min(player->hp + 20, player->maxHp);
			break;
		default:
			break;
		}
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}


Item* Item::Create(Types itemType)
{
	Item* item = new Item();
	item->type = itemType;

	switch (itemType)
	{
	case Types::AMMO:
		item->textureId = "graphics/ammo_pickup.png";
		break;
	case Types::HEAL:
		item->textureId = "graphics/health_pickup.png";
		break;
	default:
		break;
	}

	return item;
}