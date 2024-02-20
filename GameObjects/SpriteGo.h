#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;

public:
	SpriteGo(const std::string& name = "");

	void SetTexture(const std::string& textureId);
	void SetTexture(const sf::Texture& texture);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void Draw(sf::RenderWindow& window) override;

};

