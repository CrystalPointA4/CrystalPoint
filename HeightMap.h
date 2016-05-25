#pragma once
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
	void GetHeigth(float x, float z);
	void SetTexture(const std::string &file);

	std::vector<Vertex> vertices;
};

