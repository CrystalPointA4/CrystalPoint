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
	int scale;
public:
	HeightMap(const std::string &file, float scale, World* world);
	~HeightMap();

	void Draw();
	float GetHeight(float x, float y);
	void SetTexture(const std::string &file);

	std::vector<Vertex> vertices;
};

