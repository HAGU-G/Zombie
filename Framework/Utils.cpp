#include "pch.h"
#include "Utils.h"

float Utils::Clamp(float v, float min, float max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)
{
	return sf::Vector2f(Clamp(v.x, rect.left, rect.left + rect.width), Clamp(v.y, rect.top, rect.top + rect.height));
}

sf::FloatRect Utils::ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta)
{
	sf::FloatRect newRect = rect;
	newRect.width += delta.x;
	newRect.height += delta.y;

	newRect.left -= delta.x * 0.5f;
	newRect.top -= delta.y * 0.5f;

	return newRect;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= max - min;
	value += min;
	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0.f, 360.f));
	return rotation * sf::Vector2f(1.f, 0.f);
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

int Utils::RandomRange(int min, int maxExclude)
{
	int range = maxExclude - min;
	int rand = std::rand() % range;
	rand += min;
	return rand;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect Width, Height
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f Utils::GetNormalize(const sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return { 0, 0 };
	return vec / mag;
}

void Utils::Normalize(sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag != 0.f)
	{
		vec /= mag;
	}
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::DistancePointAndLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2)
{
	float a = -(lineP1 - lineP2).y / (lineP1 - lineP2).x;

	return abs(a * p1.x + p1.y) / sqrt(a * a + 1.f);
}

float Utils::DistancePointAndLineSegmentMin(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2)
{

	std::initializer_list<float> values = { Distance(lineP1,p1), Distance(lineP2,p1),
		DistancePointAndLineSegment(p1,lineP1,lineP2) };

	return std::min(values);
}

float Utils::RadianToDegree(float radian)
{
	return radian / M_PI * 180.f;
}

float Utils::DegreeToRadian(float degree)
{
	return degree / 180 * M_PI;
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(atan2f(vec.y, vec.x));
}

void Utils::Rotate(sf::Vector2f& vec, float degree)
{
	vec = GetNormalize(sf::Transform().rotate(degree) * vec);
}

void Utils::ElasticCollision(float& coord, float border, float cor)
{
	coord = border - (coord - border) * cor;
}

float Utils::GetElasticCollision(float coord, float border, float cor)
{
	return border - (coord - border) * cor;
}

bool Utils::IsCollideWithLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2, float radius)
{
	//두 점과의 거리 검사
	if (Magnitude(lineP1 - p1) <= radius || Magnitude(lineP2 - p1) <= radius)
		return true;

	//좌표계 원점 변환, 기준점 설정
	sf::Vector2f Point1 = lineP1.y < lineP2.y ? lineP1 - p1 : lineP2 - p1;
	sf::Vector2f Point2 = lineP1.y < lineP2.y ? lineP2 - p1 : lineP1 - p1;

	float angle1 = acosf(Point1.x / Utils::Magnitude(Point1));
	float angle2 = acosf(Point2.x / Utils::Magnitude(Point2));
	if (Point1.y < 0)
		angle1 = 2.f * M_PI - angle1;
	if (Point2.y < 0)
		angle2 = 2.f * M_PI - angle2;
	if (angle2 > angle1)
	{
		float temp = angle1;
		angle1 = angle2;
		angle2 = temp;

		sf::Vector2f temp2 = Point1;
		Point1 = Point2;
		Point2 = temp2;
	}
	sf::Vector2f inverseSlopePoint = { (Point1 - Point2).y, -(Point1 - Point2).x };
	float inverseSlopeAngle = acosf(inverseSlopePoint.x / Utils::Magnitude(inverseSlopePoint));
	if (inverseSlopePoint.y < 0)
		inverseSlopeAngle = 2.f * M_PI - inverseSlopeAngle;

	//선분과 닿을 수 있는 각도인지 검사
	bool check1 = false;
	if (angle1 - angle2 > M_PI && (inverseSlopeAngle >= angle1 || inverseSlopeAngle <= angle2))
	{
		check1 = true;

		float temp = angle1;
		angle1 = angle2;
		angle2 = temp;

		sf::Vector2f temp2 = Point1;
		Point1 = Point2;
		Point2 = temp2;
	}
	else if (inverseSlopeAngle <= angle1 && inverseSlopeAngle >= angle2)
	{
		check1 = true;
	}

	//선분과의 거리 검사
	if (check1)
	{
		if (Point1.y * Point2.y >= 0)
		{
			if (angle1 > M_PI)
				angle1 = 2.f * M_PI - angle1;
			if (inverseSlopeAngle > M_PI)
				inverseSlopeAngle = 2.f * M_PI - inverseSlopeAngle;

			if (Utils::Magnitude(Point1) * cos(angle1 - inverseSlopeAngle) <= radius)
				return true;
		}
		else if (Point1.x * Point2.x >= 0 || inverseSlopeAngle <= M_PI_2 || (inverseSlopeAngle >= M_PI && inverseSlopeAngle <= M_PI + M_PI_2))
		{
			angle1 = asinf(Point1.y / Utils::Magnitude(Point1));
			angle2 = asinf(Point2.y / Utils::Magnitude(Point2));
			inverseSlopeAngle = asinf(inverseSlopePoint.y / Utils::Magnitude(inverseSlopePoint));

			if (Utils::Magnitude(Point2) * cos(angle2 - inverseSlopeAngle) <= radius)
				return true;
		}
		else if (inverseSlopeAngle >= M_PI + M_PI_2 || (inverseSlopeAngle >= M_PI_2 && inverseSlopeAngle <= M_PI))
		{
			if (angle2 > M_PI)
				angle2 = 2.f * M_PI - angle2;
			if (inverseSlopeAngle > M_PI)
				inverseSlopeAngle = 2.f * M_PI - inverseSlopeAngle;

			if (Utils::Magnitude(Point2) * cos(angle2 - inverseSlopeAngle) <= radius)
				return true;
		}
	}
	return false;
}