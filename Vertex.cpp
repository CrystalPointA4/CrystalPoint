#include "Vertex.h"

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz, float tx, float ty)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->normalX = nx;
	this->normalY = ny;
	this->normalZ = nz;

	this->texX = tx;
	this->texY = ty;
}

Vertex::~Vertex()
{
}

Vertex Vertex::operator/(const float &other) const
{
	return Vertex(x / other, y / other, z / other, normalX, normalY, normalZ, texX, texY);
}

Vertex Vertex::operator*(const Vertex & other) const
{
	return Vertex(x*other.x, y*other.y, z*other.z, normalX, normalY, normalZ, texX, texY);
}

Vertex Vertex::operator*(const float & other) const
{
	return Vertex(x*other, y*other, z*other, normalX, normalY, normalZ, texX, texY);
}

Vertex Vertex::operator+(const Vertex & other) const
{
	return Vertex(x+other.x, y+other.y, z+other.z, normalX, normalY, normalZ, texX, texY);
}
