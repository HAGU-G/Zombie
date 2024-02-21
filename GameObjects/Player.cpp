#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
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
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	//캐릭터 회전
	sf::Vector2f mouseWorldPos = InputMgr::GetMousePos();
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


	//충돌 검사
	sf::Vector2f fixPos = GetPosition() + direction * speed * dt;
	sf::FloatRect windowBound({ 0,0 ,(float)Framework::Instance().GetWindowSize().x, (float)Framework::Instance().GetWindowSize().y });

	//충돌 검사: 윈도우
	if (fixPos.x < windowBound.left + sprite.getLocalBounds().width / 3)
		Utils::ElasticCollision(fixPos.x, windowBound.left + sprite.getLocalBounds().width / 3, 0.f);
	if (fixPos.x > windowBound.width - sprite.getLocalBounds().width / 3)
		Utils::ElasticCollision(fixPos.x, windowBound.width - sprite.getLocalBounds().width / 3, 0.f);
	if (fixPos.y < windowBound.top + sprite.getLocalBounds().height / 3)
		Utils::ElasticCollision(fixPos.y, windowBound.top + sprite.getLocalBounds().height / 3, 0.f);
	if (fixPos.y > windowBound.height - sprite.getLocalBounds().height / 3)
		Utils::ElasticCollision(fixPos.y, windowBound.height - sprite.getLocalBounds().height / 3, 0.f);
	SetPosition(fixPos);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
