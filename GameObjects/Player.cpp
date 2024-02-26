#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "Item2.h"
#include "UIHUD.h"
#include "Crosshair.h"

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

	isFiring = false;
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
	hud = dynamic_cast<UIHUD*>(SCENE_MGR.GetCurrentScene()->FindGo("UIHUD"));

	ammo = maxAmmo;
	totalAmmo = ammo;
	hud->SetAmmo(ammo, totalAmmo);
	hud->SetHp(hp, maxHp);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	shotTimer += dt;
	damagedTimer += dt;
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
		if (shotTimer >= shotInterval)
		{
			shotTimer = 0.f;
			Shot();
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		if (shotTimer >= shotInterval)
		{
			shotTimer = 0.f;
			Shot();
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
			shotTimer = -1.f;
			int needAmmo = maxAmmo - ammo;
			if (totalAmmo >= needAmmo)
			{
				ammo += needAmmo;
				totalAmmo -= needAmmo;
				hud->SetAmmo(ammo, totalAmmo);
			}
			else
			{
				ammo += totalAmmo;
				totalAmmo = 0;
				hud->SetAmmo(ammo, totalAmmo);
			}
			dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->crosshair->MotionReload();
	}

	//죽음
	if (hp == 0)
	{
		onDie();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::onDamage(int damage)
{
	if (damagedTimer >= damagedInterval)
	{
		damagedTimer = 0.f;
		hp = std::max(hp - damage, 0);
		hud->SetHp(hp, maxHp);
	}
}


void Player::Shot()
{
	if (ammo > 0)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->CreateBullet(this);
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->crosshair->MotionShot();
		SOUND_MGR.PlaySfx("sound/shoot.wav");
	}
	
	//Bullet2* bullet = new Bullet2();
	//bullet->Init();
	//bullet->Fire(direction, 150.f);
	//SCENE_MGR.GetCurrentScene()->AddGo(bullet)->SetPosition(position);
}

void Player::onDie()
{
	active = false;
	SOUND_MGR.PlayBGM("sound/SellBuyMusic2.wav");
}

void Player::onItem(Item2* item)
{
	switch (item->GetType())
	{
	case Item2::Types::AMMO:
		totalAmmo += item->GetValue();
		hud->SetAmmo(ammo, totalAmmo);
		break;
	case Item2::Types::HEALTH:
		hp = std::min(hp+item->GetValue(),maxHp);
		hud->SetHp(hp,maxHp);
		break;
	}
}
