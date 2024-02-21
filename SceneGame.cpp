#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	player->SetPosition(centerPos);
	tileMap->SetPosition(centerPos);
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetRotation(10);
	tileMap->UpdateTransform();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
