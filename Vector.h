#pragma once

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(const Vec3f &other);
	Vec3f(float x, float y, float z);
	float Length();
	void Normalize();
	float Distance(const Vec3f &);
	float& operator [](int);
	Vec3f operator + (const Vec3f &other);
	Vec3f operator -(const Vec3f &other);
	Vec3f operator / (float value);
	bool operator ==(const Vec3f &other);
	bool operator !=(const Vec3f &other);
	Vec3f operator *(const float &other);

	Vec3f cross(const Vec3f &other);

};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(const Vec2f &other);
	float& operator [](int);
	Vec2f operator + (const Vec2f &other);
	float length();	
};

