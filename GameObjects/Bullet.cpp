#include "pch.h"
#include "Bullet.h"
#include "Player.h"
#include "SceneGame.h"

Bullet::Bullet(const sf::Vector2f& position, const std::string& name)
	:GameObject(name), speed(3000), damage(34)
{
	sortLayer = 4;
	tag = 1;
	shape.setSize({ 3.f, 2.f });
	shape.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(shape, Origins::MR);

	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
	Utils::Normalize(direction = mouseWorldPos - position);
	shape.rotate(Utils::Angle(direction));

	SetPosition(position + direction * 20.f);
	shape.setPosition(this->position);

	shape.setScale({ 0.f , 1.f });
	prePos = position;
}

void Bullet::Init()
{
	GameObject::Init();
}

void Bullet::Release()
{
	GameObject::Release();
}

void Bullet::Reset()
{
	GameObject::Reset();
}

void Bullet::Update(float dt)
{
	if (isStuckInWall)
		Hit();
	prePos = position;

	GameObject::Update(dt);
	Translate(direction * speed * dt);

	//충돌 검사
	std::pair<sf::Vector2f, sf::Vector2f> boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	//충돌 검사: 벽
	if (position.x < boundary.first.x)
	{
		position.y -= (position.x - boundary.first.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.first.x, 0.f);
		isStuckInWall = true;
	}
	if (position.x > boundary.second.x)
	{
		position.y -= (position.x - boundary.second.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.second.x, 0.f);
		isStuckInWall = true;
	}
	if (position.y < boundary.first.y)
	{
		position.x -= (position.y - boundary.first.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.first.y, 0.f);
		isStuckInWall = true;
	}
	if (position.y > boundary.second.y)
	{
		position.x -= (position.y - boundary.second.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.second.y, 0.f);
		isStuckInWall = true;
	}

	//총알 흔적
	shape.setPosition(position);
	float distance = Utils::Distance(prePos, position);
	shape.setScale({ 1.f + distance / 3,1.f });

}

void Bullet::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(shape);
	if (isHit)
	{
		active = false;
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);
	}
}

void Bullet::Hit()
{
	if (!isHit)
	{
		isHit = true;
	}
}

Bullet* Bullet::Create(Player* player)
{
	Bullet* bullet = new Bullet(player->GetPosition());
	bullet->Init();
	return bullet;
}
