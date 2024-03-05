#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "AniTest.h"
#include "AniTop.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{
	ground.setFillColor(sf::Color::White);
	ground.setSize({ 500,500 });
	Utils::SetOrigin(ground, Origins::MC);
	ground.setPosition(sf::Vector2f(FRAMEWORK.GetWindowSize()) * 0.5f);
	ground.rotate(45);


	aniTest = new AniTest();
	AddGo(aniTest);
	aniTop = new AniTop();
	AddGo(aniTop);

	Scene::Init();

	aniTest->Reset();
	aniTest->SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize()) * 0.5f);


	aniTop->Reset();
	aniTop->SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize()) * 0.5f);


}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}
	if (!(aniTest->onGround) && aniTest->GetGlobalBounds().intersects(ground.getGlobalBounds()))
	{
		aniTest->SetPosition({ aniTest->GetPosition().x, ground.getPosition().y });
		aniTest->onGround = true;
		aniTest->jumpSpeed = 0.f;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
	SOUND_MGR.PlayBGM("sound/SellBuyMusic1.wav");



}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.draw(ground);
	Scene::Draw(window);
}
