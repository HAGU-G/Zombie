#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) :
	id(id),
	texResMgr(RES_MGR_TEXTURE),
	fontResMgr(RES_MGR_FONT),
	soundResMgr(RES_MGR_SOUND_BUFFER)
{
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->name == name)
		{
			return obj;
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->name == name)
		{
			list.push_back(obj);
		}
	}
	return list.size();
}

GameObject* Scene::AddGo(GameObject* obj)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
	{
		gameObjects.push_back(obj);
		return obj;
	}
	return nullptr;
}

void Scene::RemoveGo(GameObject* obj)
{
	gameObjects.remove(obj);
}
