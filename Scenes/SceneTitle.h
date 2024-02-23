#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:

public:
	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	virtual void Init();
	virtual void Update(float dt);
};

