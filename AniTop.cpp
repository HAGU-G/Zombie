#include "pch.h"
#include "AniTop.h"


AniTop::AniTop(const std::string& name)
	:SpriteGo(name)
{
}

void AniTop::Init()
{
	SpriteGo::Init();
	int tileSize = 256;
	////////////////////////////////////////IDLE
	animator.SetTarget(&sprite);

	SetOrigin({ tileSize * 0.5f, (float)tileSize });

	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", false, Utils::GetNormalize({-1, -1}) });
	clipInfos.push_back({ "data/IdleUp.csv", "data/MoveUp.csv", false, {0, -1} });
	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", true, Utils::GetNormalize({1, -1}) });
	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", true, {1, 0} });
	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", true, Utils::GetNormalize({1, 1}) });
	clipInfos.push_back({ "data/IdleDown.csv", "data/MoveDown.csv", false, {0, 1} });
	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", false, Utils::GetNormalize({-1, 1}) });
	clipInfos.push_back({ "data/IdleSide.csv", "data/MoveSide.csv", false, {-1, 0} });

}

void AniTop::Release()
{
	SpriteGo::Release();
}

void AniTop::Reset()
{
	animator.Play("data/IdleDown.csv");
	currentClipInfo = &clipInfos[5];
}

void AniTop::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);


	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		direction /= mag;
	}
	Translate(direction * speed * dt);



	std::string clipId;
	if (direction.x != 0.f || direction.y != 0.f)
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs)
			{
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
			});
		currentClipInfo = &*min;
		clipId = currentClipInfo->move;
	}
	else
	{
		clipId = currentClipInfo->idle;
	}

	SetFlipX(currentClipInfo->flipX);
	if (animator.GetCurrentClip() != clipId)
	{
		animator.Play(clipId);
	}

}

void AniTop::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void AniTop::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void AniTop::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
