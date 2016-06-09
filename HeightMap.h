#pragma once
#include "Vertex.h"

#include <string>
#include <vector>
#include <GL/freeglut.h>

class World;

class HeightMap
{
private:
	int height;
	int width;

	GLuint imageIndex;
public:
	HeightMap(const std::string &file, World* world);
	~HeightMap();

	void Draw();
	float GetHeight(float x, float y);
	int GetSize();
	void SetTexture(const std::string &file);

	std::vector<Vertex> vertices;
};

