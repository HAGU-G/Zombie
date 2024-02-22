#include "pch.h"
#include "Bullet.h"
#include "Player.h"

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

	SetPosition(position + direction * shape.getSize().x);
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
	prePos = position;

	GameObject::Update(dt);
	Translate(direction * speed * dt);
	shape.setPosition(position);
	float distance = Utils::Distance(prePos, position);

	if (displacement >= 15.f)
		shape.setScale({ 1.f + distance / 3,1.f });
	else
		displacement += distance;
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

void Bullet::Hit(sf::Vector2f hitedObjectPos)
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
