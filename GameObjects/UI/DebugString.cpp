#include "pch.h"
#include "DebugString.h"

DebugString::DebugString(const std::string& name)
	:GameObject(name)
{
}

void DebugString::Init()
{
	GameObject::Init();

	a.setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
	b.setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
	c.setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
	d.setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));

	a.setCharacterSize(20);
	b.setCharacterSize(20);
	c.setCharacterSize(20);
	d.setCharacterSize(20);

	a.setPosition(0, 0);
	b.setPosition(0, 20);
	c.setPosition(0, 40);
	d.setPosition(0, 60);

	a.setString("a");
	b.setString("b");
	c.setString("c");
	d.setString("d");

}

void DebugString::Release()
{
	GameObject::Release();
}

void DebugString::Reset()
{
	GameObject::Reset();
}

void DebugString::Update(float dt)
{
	GameObject::Update(dt);
}

void DebugString::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void DebugString::FixedUpdate(float dt)
{
	GameObject::FixedUpdate(dt);
}

void DebugString::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(a);
	window.draw(b);
	window.draw(c);
	window.draw(d);
}
