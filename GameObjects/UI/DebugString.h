#pragma once
#include "GameObject.h"

class DebugString : public GameObject
{

public:	
	
	sf::Text a;
	sf::Text b;
	sf::Text c;
	sf::Text d;



	DebugString(const std::string& name = "Debug");
	~DebugString() override = default;


	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};