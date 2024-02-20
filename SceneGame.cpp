#include "pch.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	player = new Player("Player");
	AddGo(player);
	player->SetPosition({ 960,540 });

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
