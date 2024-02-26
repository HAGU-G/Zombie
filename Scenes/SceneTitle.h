#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:

public:
	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;

};

