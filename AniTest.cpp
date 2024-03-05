#include "pch.h"
#include "AniTest.h"

AniTest::AniTest(const std::string& name)
	:SpriteGo(name)
{
}

void AniTest::TestInstance()
{
	std::cout << "TestInstance()" << std::endl;
}

void AniTest::TestStatic()
{
	std::cout << "TestStatic()" << std::endl;
}

void AniTest::Init()
{
	SpriteGo::Init();
	animator.SetTarget(&sprite);

	SetOrigin({ 60, 120 });
}

void AniTest::Release()
{
	SpriteGo::Release();
}

void AniTest::Reset()
{

	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&AniTest::TestInstance, this);
	//this �� ���� �Ű������� �Է�.
	//std::placeholder::_1�� �Է��ϸ� �Ű������� ��ǰ�ü���� �Ѱ��� �� �ִ�.
	animator.AddEvent("data/Jump.csv", 6, funcInstance);

	std::function<void()> funcStatic = std::bind(&AniTest::TestStatic);
	animator.AddEvent("data/Jump.csv", 1, funcStatic);

	animator.Play("data/Idle.csv");
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);


	//����
	if (onGround)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			animator.Play("data/Jump.csv");
			jumpSpeed = -200.f;
			onGround = false;
		}
	}
	else
	{
		jumpSpeed += 300.f * dt;
	}

	//�̵�
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	Utils::Normalize(direction);
	if (abs(direction.x) > 0.f)
	{
		if (animator.GetCurrentClip() != "data/Run.csv" && onGround)
			animator.Play("data/Run.csv");
		SetFlipX(direction.x < 0.f);
	}
	sf::Vector2f tempPos(GetPosition() + direction * speed * dt);
	tempPos.y += jumpSpeed * dt;
	SetPosition(tempPos);

	//����
	if (onGround && direction.x == 0.f)
	{
		if (animator.GetCurrentClip() != "data/Idle.csv")
			animator.Play("data/Idle.csv");
	}

}

void AniTest::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void AniTest::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void AniTest::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
