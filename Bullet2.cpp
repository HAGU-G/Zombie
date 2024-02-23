#include "pch.h"
#include "Bullet2.h"
#include "SceneGame.h"

Bullet2::Bullet2(const std::string& name)
:SpriteGo(name)
{

}

void Bullet2::Fire(const sf::Vector2f& dir, float s)
{
	direction = dir;
	speed = s;

	SetRotation(Utils::Angle(direction));
}

void Bullet2::Init()
{
	SpriteGo::Init();
	textureId = "graphics/bullet.png";
	SetTexture(textureId);
	SetOrigin(Origins::ML);

}

void Bullet2::Reset()
{
	SpriteGo::Reset();

}

void Bullet2::Update(float dt)
{
	SpriteGo::Update(dt);
	SetPosition(position + direction * speed * dt);
	//충돌 검사
	std::pair<sf::Vector2f, sf::Vector2f> boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	//충돌 검사: 벽
	if (position.x < boundary.first.x)
	{
		position.y -= (position.x - boundary.first.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.first.x, 0.f);
	}
	if (position.x > boundary.second.x)
	{
		position.y -= (position.x - boundary.second.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.second.x, 0.f);
	}
	if (position.y < boundary.first.y)
	{
		position.x -= (position.y - boundary.first.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.first.y, 0.f);
	}
	if (position.y > boundary.second.y)
	{
		position.x -= (position.y - boundary.second.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.second.y, 0.f);
	}
	SetPosition(position);
}
