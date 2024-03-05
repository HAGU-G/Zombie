#pragma once
#include "Scene.h"

class AniTest;
class AniTop;

class SceneTitle : public Scene
{
protected:
	sf::RectangleShape ground;
	AniTest* aniTest = nullptr;
	AniTop* aniTop = nullptr;

public:
	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;

};

