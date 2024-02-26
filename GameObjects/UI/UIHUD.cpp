#include "pch.h"
#include "UIHUD.h"

UIHUD::UIHUD(const std::string& name)
	:GameObject(name)
{
}

void UIHUD::Init()
{
	GameObject::Init();

	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");
	textAmmo.Set(font, "", textSize, sf::Color::White);
	gaugeHpSize = { 300.f,60.f };
	gaugeHp.setSize(gaugeHpSize);
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeMaxHp.setSize(gaugeHpSize);
	gaugeMaxHp.setFillColor(sf::Color(40,40,40,255));
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	Utils::SetOrigin(gaugeMaxHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	//Top
	float topY = 50.f;

	textScore.SetPosition({ 50.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 50.f, topY });

	//Bottom
	float BottomY = referenceResolution.y - 50.f;
	imgAmmoIcon.SetPosition({ 50.f, BottomY + 6.f });
	textAmmo.SetPosition({ 150.f, BottomY });
	gaugeHp.setPosition({ 450.f, BottomY + 6.f });
	gaugeMaxHp.setPosition(gaugeHp.getPosition());
	textWave.SetPosition({ referenceResolution.x - 550.f, BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 50.f, BottomY });

	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();
}

void UIHUD::Release()
{
	GameObject::Release();
}

void UIHUD::Reset()
{
	GameObject::Reset();
}

void UIHUD::Update(float dt)
{
	GameObject::Update(dt);
}

void UIHUD::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UIHUD::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	textAmmo.Draw(window);
	window.draw(gaugeMaxHp);
	window.draw(gaugeHp);
	textWave.Draw(window);
	textZombieCount.Draw(window);
}

void UIHUD::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UIHUD::SetHiScore(int s)
{
	textHiScore.SetString(formatHiScore + std::to_string(s));
}

void UIHUD::SetAmmo(int current, int total)
{
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total));
}

void UIHUD::SetHp(int hp, int max)
{
	float value = max > 0 ? (float)hp / max : 0;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UIHUD::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UIHUD::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UIHUD::SetResolution(const sf::Vector2f resolution)
{
}
