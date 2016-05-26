#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector.h"

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
/*The length of the vector*/
float Vec3f::Length()
{
	return (float)sqrt(x*x+y*y+z*z);
}

void Vec3f::Normalize()
{	
	float length = this->Length();

	if (length != 0)
	{
		x = x / length;
		y = y / length;
		z = z / length;
	}
}

float Vec3f::Distance(const Vec3f &other)
{
	return (float)sqrt(pow(other.x - x, 2)+pow(other.y - y, 2)+pow(other.z - z, 2));
}

Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec3f Vec3f::operator+(const Vec3f & other)
{
	return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f Vec3f::operator-(const Vec3f & other)
{
	return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::operator/(float value)
{
	return Vec3f(x / value, y / value, z / value);
}

bool  Vec3f::operator==(const Vec3f & other)
{
	/*bool xb, yb,zb;
	xb = x == other.x;
	yb = y == other.y;
	zb = z == other.z;
	if (xb & yb & zb)
		return true;*/
	return x == other.x & y == other.y & z == other.z;
}

bool Vec3f::operator!=(const Vec3f & other)
{
	return x != other.x & y != other.y & z != other.z;
}

Vec3f Vec3f::operator*(const float & other)
{
	return Vec3f(x*other, y*other, z*other);
}

Vec3f Vec3f::cross(const Vec3f & other)
{
	return Vec3f(
		y*other.z - other.y*z,
		z*other.x - other.z*x,
		x*other.y - other.x*y
		);
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(const Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

Vec2f Vec2f::operator+(const Vec2f & other)
{
	return Vec2f(x + other.x, y+other.y);
}

float Vec2f::length()
{
	return (float)sqrt(x*x + y*y);
}

