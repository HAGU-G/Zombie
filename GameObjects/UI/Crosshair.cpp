#include "pch.h"
#include "Crosshair.h"

Crosshair::Crosshair(const std::string& name)
	:SpriteGo(name)
{
	sortLayer = 20;
	textureId = "graphics/crosshair.png";
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Crosshair::Init()
{
	SpriteGo::Init();
}

void Crosshair::Release()
{
	SpriteGo::Release();
}

void Crosshair::Reset()
{
	SpriteGo::Reset();
}

void Crosshair::Update(float dt)
{
	SpriteGo::Update(dt);
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi((sf::Vector2i)InputMgr::GetMousePos());
	SetPosition(mouseWorldPos);
}

void Crosshair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
