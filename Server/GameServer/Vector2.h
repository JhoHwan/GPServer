#include <iostream>
#include <cmath>

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
		return x * rhs.x + y *  rhs.y;
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

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3() : Vector3(0, 0, 0) {}
	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	Vector3 operator+(const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 operator*(double scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator/(double scalar) const
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	double Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 Normalize() const
	{
		double length = Length();
		return Vector3(x / length, y / length, z / length);
	}

    Vector2 Normalize2D() const
    {
        Vector2 vec2(x, y);
        return vec2.Normalize();
    }

	double Dot(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3 Cross(const Vector3& rhs) const
	{
		return Vector3(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		);
	}

	Vector3 Reflect(const Vector3& normal) const
	{
		return *this - normal * 2.0 * Dot(normal);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

	static Vector3 Lerp(const Vector3& start, const Vector3& end, double t)
	{
		return start * (1.0 - t) + end * t;
	}

	static double Distance(const Vector3& a, const Vector3& b)
	{
		return (a - b).Length();
	}

    static Vector3 GetDirectionFromYaw(const double& yaw)
    {
        double radian = yaw * 3.14159265358979323846 / 180.0;
        return Vector3(cos(radian), sin(radian), 0).Normalize();
    }

	static Vector3 Zero() { return Vector3(0, 0, 0); }
	static Vector3 One() { return Vector3(1, 1, 1); }
	static Vector3 Up() { return Vector3(0, 1, 0); }
	static Vector3 Down() { return Vector3(0, -1, 0); }
	static Vector3 Left() { return Vector3(-1, 0, 0); }
	static Vector3 Right() { return Vector3(1, 0, 0); }
	static Vector3 Forward() { return Vector3(0, 0, 1); }
	static Vector3 Backward() { return Vector3(0, 0, -1); }
};

struct YawRotation
{
    double yaw;

    YawRotation() : yaw(0) {}
    YawRotation(double yaw) : yaw(yaw) {}

    YawRotation operator+(const YawRotation& rhs) const
    {
        return YawRotation(yaw + rhs.yaw);
    }

    YawRotation operator-(const YawRotation& rhs) const
    {
        return YawRotation(yaw - rhs.yaw);
    }

    YawRotation& operator=(const YawRotation& rhs)
    {
        if (this != &rhs)
        {
            yaw = rhs.yaw;
        }
        return *this;
    }

    YawRotation& operator=(const double& rhs)
    {
        yaw = rhs;
        return *this;
    }

    operator double() const
    {
        return yaw;
    }

    bool operator==(const double& rhs) const
    {
        return yaw == rhs;
    }

    bool operator!=(const double& rhs) const
    {
        return yaw != rhs;
    }

    bool operator<(const double& rhs) const
    {
        return yaw < rhs;
    }

    bool operator<=(const double& rhs) const
    {
        return yaw <= rhs;
    }

    bool operator>(const double& rhs) const
    {
        return yaw > rhs;
    }

    bool operator>=(const double& rhs) const
    {
        return yaw >= rhs;
    }

	void RotateTowards(const YawRotation& target, double maxStep)
	{
		double diff = YawRotation::GetYawDifference(target, *this); // 올바른 순서
		if (abs(diff) <= maxStep)
			yaw = target.yaw;
		else
			yaw += (diff > 0 ? 1 : -1) * maxStep;
	}

	static YawRotation GetYawFromDirection(const Vector3& direction)
	{
		double yaw = atan2(direction.y, direction.x) * 180.0 / 3.14159265358979323846;

		return yaw;
	}

    static YawRotation GetYawDifference(const YawRotation& yaw1, const YawRotation& yaw2)
    {
        double diff = fmod(yaw2.yaw - yaw1.yaw + 180.0, 360.0) - 180.0;
        return diff < -180.0 ? diff + 360.0 : diff;
    }

    static YawRotation Lerp(const YawRotation& start, const YawRotation& end, double t)
    {
        double lerpedYaw = start.yaw * (1.0 - t) + end.yaw * t;
        return YawRotation(lerpedYaw);
    }

    friend std::ostream& operator<<(std::ostream& os, const YawRotation& vec)
    {
        os << vec.yaw;
        return os;
    }
};
