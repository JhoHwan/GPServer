#include <iostream>

struct Vector2
{
	double x;
	double y;

	Vector2() : Vector2(0, 0) {}
	Vector2(double x, double y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator*(double scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(double scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	double Length() const
	{
		return sqrt(x * x + y * y);
	}

	Vector2 Normalize() const
	{
		double length = Length();
		return Vector2(x / length, y / length);
	}

	double Dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	double Cross(const Vector2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	Vector2 Rotate(double angle) const
	{
		double radian = angle * 3.14159265358979323846 / 180.0;
		double cosValue = cos(radian);
		double sinValue = sin(radian);
		return Vector2(x * cosValue - y * sinValue, x * sinValue + y * cosValue);
	}

	Vector2 Reflect(const Vector2& normal) const
	{
		return *this - normal * 2.0 * Dot(normal);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	static Vector2 Lerp(const Vector2& start, const Vector2& end, double t)
	{
		return start * (1.0 - t) + end * t;
	}

	static Vector2 Slerp(const Vector2& start, const Vector2& end, double t)
	{
		double dot = start.Dot(end);
		dot = fmax(-1.0, fmin(1.0, dot));
		double theta = acos(dot) * t;
		Vector2 relative = (end - start * dot).Normalize();
		return start * cos(theta) + relative * sin(theta);
	}

	static float Distance(const Vector2& a, const Vector2& b)
	{
		return (a - b).Length();
	}

	static Vector2 Zero() { return Vector2(0, 0); }
	static Vector2 One() { return Vector2(1, 1); }
	static Vector2 Up() { return Vector2(0, 1); }
	static Vector2 Down() { return Vector2(0, -1); }
	static Vector2 Left() { return Vector2(-1, 0); }
	static Vector2 Right() { return Vector2(1, 0); }
};

template <>
struct std::formatter<Vector2> : std::formatter<std::string> {
	// format �Լ� ����
	auto format(const Vector2& v, format_context& ctx) const {
		std::string s = std::format("({:.2f}, {:.2f})", v.x, v.y);
		return std::formatter<std::string>::format(s, ctx);
	}
};