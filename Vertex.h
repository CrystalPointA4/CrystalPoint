#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z, float nx, float ny, float nz, float tx, float ty);
	~Vertex();

	float x;
	float y;
	float z;

	float normalX;
	float normalY;
	float normalZ;

	float texX;
	float texY;
};

