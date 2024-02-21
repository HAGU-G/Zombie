#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	std::string spriteSheetId;
	sf::Texture* texture;

	int rows = 10;
	int cols = 10;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;


	sf::Transform transform;

public:
	sf::VertexArray va;
	TileMap(const std::string& name = "name");
	~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void SetSpriteSheetId(const std::string& id);
	void UpdateTransform();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;



	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float r) override;
	void Translate(const sf::Vector2f& delta) override;

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

};
