#pragma once
#include "Vertex.h"

#include <string>
#include <vector>
#include <GL/freeglut.h>

class HeightMap
{
private:
	int height;
	int width;

	GLuint imageIndex;
	int scale = 1;
public:
	HeightMap(const std::string &file);
	~HeightMap();

	void Draw();
	float GetHeigth(float x, float y);
	void SetTexture(const std::string &file);

	std::vector<Vertex> vertices;
};

