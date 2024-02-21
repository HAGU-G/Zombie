#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	:GameObject(name)
{
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipX ? -scale.y : scale.y;

	transform.scale(scaleX, scaleY, position.x , position.y);
	transform.rotate(rotation, position.x, position.y);
	transform.translate(position - origin);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f posOffsets[4] = {
		{0,0},
		{size.x,0},
		{size.x,size.y},
		{0,size.y}
	};

	for (int i = 0; i < count.y; ++i)
	{
		for (int j = 0; j < count.x; ++j)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
				texIndex = 3;

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(size.x * j, size.y * i);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadPos + posOffsets[k];
				va[vertexIndex].texCoords = sf::Vector2f(0, texIndex * size.y) + posOffsets[k];
			}
		}
	}
}

void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheetId("graphics/background_sheet.png");
	//50x50
	Set({ 20, 10 }, { 50.f, 50.f });
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);
}

void TileMap::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;

	window.draw(va, state);
}

void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	originPreset = preset;
	sf::FloatRect bound = va.getBounds();
	origin.x = bound.width * ((int)originPreset % 3) * 0.5f;
	origin.y = bound.height * ((int)originPreset % 3) * 0.5f;

	//sf::Vector2f newOrigin(bound.width, bound.height);
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	UpdateTransform();
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
	//sf::Vector2f delta = pos - position;
	//for (int i = 0; i < va.getVertexCount(); i++)
	//{
	//	va[i].position += delta;
	//	position = pos;
	//}
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	UpdateTransform();


	//this->scale = scale;
	//float x0 = origin.x*this->scale.x;
	//float y0 = origin.y * this->scale.y;
	//for (int i = 0; i < va.getVertexCount(); i++)
	//{
	//	va[i].position.x += (va[i].position.x - x0) * (this->scale.x - 1.f)/2;
	//	va[i].position.y += (va[i].position.y - y0) * (this->scale.y - 1.f)/2;
	//}
}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}
