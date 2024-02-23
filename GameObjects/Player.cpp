#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "TileMap.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
	sortLayer = 5;
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

}

void Player::Release()
{
	SpriteGo::Init();
}

void Player::Reset()
{
	SpriteGo::Reset();
	active = true;

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	//캐릭터 회전
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	//sf::Vector2f mouseWorldPos = InputMgr::GetMousePos() + SCENE_MGR.GetCurrentScene()->GetViewCenter() - sf::Vector2f(FRAMEWORK.GetWindow().getSize()) * 0.5f;
	float lookAngle = Utils::Angle(mouseWorldPos - GetPosition());
	Utils::Rotate(look, lookAngle);
	SetRotation(lookAngle);

	//캐릭터 이동
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f tempPos(GetPosition() + direction * speed * dt);

	//충돌 검사
	boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	// 
	//충돌 검사: 벽
	if (tempPos.x < boundary.first.x)
		Utils::ElasticCollision(tempPos.x, boundary.first.x, 0.f);
	if (tempPos.x > boundary.second.x)
		Utils::ElasticCollision(tempPos.x, boundary.second.x, 0.f);
	if (tempPos.y < boundary.first.y)
		Utils::ElasticCollision(tempPos.y, boundary.first.y, 0.f);
	if (tempPos.y > boundary.second.y)
		Utils::ElasticCollision(tempPos.y, boundary.second.y, 0.f);

	SetPosition(tempPos);

	//Shot
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		Shot();
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		Shot();
	}

	if (hp == 0)
	{
		active = false;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Damaged(int damage)
{
	hp = std::max(hp - damage, 0);
}

void Player::Shot()
{
	dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->CreateBullet(this);

}
