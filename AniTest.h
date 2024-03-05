#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo
{
protected:
	Animator animator;
	float speed = 400.f;


public:

	sf::Vector2f direction;
	float jumpSpeed = 0;

	bool onGround = true;

	AniTest(const std::string& name = "");
	~AniTest() override = default;

	void TestInstance();
	static void TestStatic();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};
