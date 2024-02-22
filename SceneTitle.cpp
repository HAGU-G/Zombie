#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
	SpriteGo* bg = new SpriteGo("bg");
	bg->SetTexture("graphics/background.png");
	AddGo(bg, Scene::Ui);
}

void SceneTitle::Init()
{
	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::AnyKeyDown())
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}
}
