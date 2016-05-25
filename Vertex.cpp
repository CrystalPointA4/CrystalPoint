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
