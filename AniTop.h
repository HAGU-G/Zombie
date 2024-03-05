#pragma once
#include "SpriteGo.h"
#include "Animator.h"
class AniTop : public SpriteGo
{
public:
	struct ClipInfo 
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;

		ClipInfo(const std::string& idle, const std::string& move, bool flipX, const sf::Vector2f& point)
			:idle(idle), move(move), flipX(flipX), point(point)
		{

		}
		ClipInfo()
		{
		}
	};

protected: 
	Animator animator;

	sf::Vector2f direction;
	float speed = 500.f;

	std::vector<ClipInfo> clipInfos;
	ClipInfo* currentClipInfo = nullptr;

public:
	AniTop(const std::string& name = "");
	~AniTop() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

