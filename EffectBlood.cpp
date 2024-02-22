#include "pch.h"
#include "EffectBlood.h"

EffectBlood::EffectBlood(sf::Vector2f pos, const std::string& name)
	:SpriteGo(name)
{
	position = pos;
	textureId = "graphics/blood.png";
}

void EffectBlood::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
	SetPosition(position);
	sprite.rotate(Utils::RandomRange(0.f, 360.f));
}

void EffectBlood::Update(float dt)
{
	SpriteGo::Update(dt);
	scale = {scale.x-0.1f* dt , scale.y - 0.1f * dt };
	timer -= dt;
	sprite.setScale(scale);
	sf::Color color = sprite.getColor();
	color.a = scale.x*255;
	sprite.setColor(color);
	if (timer <= 0.f && !del)
	{
		del = true;
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);
	}
}

void EffectBlood::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
