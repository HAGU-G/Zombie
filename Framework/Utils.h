#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	//Math
	static float SqrMagnitude(const sf::Vector2f& vec); //길이^2
	static float Magnitude(const sf::Vector2f& vec); //길이
	static sf::Vector2f GetNormalize(const sf::Vector2f& vec); //단위벡터
	static void Normalize(sf::Vector2f& vec); //정규화
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
	static float DistancePointAndLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2);
	static float DistancePointAndLineSegmentMin(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2);

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);
	static float Angle(const sf::Vector2f& vec);
	static void Rotate(sf::Vector2f& vec, float degree); //회전

	//충돌
	static void ElasticCollision(float& coord, float border, float cor = 1.f);
	static float GetElasticCollision(float coord, float border, float cor = 1.f);
	static bool IsCollideWithLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2, float radius);

};