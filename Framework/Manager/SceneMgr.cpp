#include "pch.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "SceneTitle.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();
	scenes.push_back(new SceneTitle(SceneIds::SceneTitle));
	scenes.push_back(new SceneGame(SceneIds::SceneGame));

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	// TO-DO: 모든 게임 오브젝트 업데이트 끝난 후에 씬 전환 되도록

	scenes[(int)currentScene]->Exit();
	currentScene = id;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		ChangeScene(startScene);
	}
	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::LateUpdate(float dt)
{
	scenes[(int)currentScene]->LateUpdate(dt);
}

void SceneMgr::FixedUpdate(float dt)
{
	scenes[(int)currentScene]->FixedUpdate(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}
