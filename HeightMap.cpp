#include "HeightMap.h"
#include "stb_image.h"
#include "vector.h"

#include "LevelObject.h"

#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "World.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define ALPHA 3

HeightMap::HeightMap(const std::string &file, float scale, World* world)
{
	this->scale = scale;

	int bpp;
	unsigned char* imgData = stbi_load(file.c_str(), &width, &height, &bpp, 4);

	auto heightAt = [&](int x, int y)
	{
		return (imgData[(x + y * width) * 4 ] / 256.0f) * 100.0f;
	};

	auto valueAt = [&](int x, int y, int offset = 0)
	{
		return imgData[(x + y * width) * 4 + offset];
	};

	for (int y = 0; y < height-1; y++)
	{
		for (int x = 0; x < width-1; x++)
		{
			int offsets[4][2] = { { 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 } };
			Vec3f ca(0, heightAt(x, y + 1) - heightAt(x, y), 1);
			Vec3f ba(1, heightAt(x + 1, y) - heightAt(x, y), 0);


			if ((valueAt(x, y, GREEN) >= 10) && (valueAt(x,y,GREEN) <= 100))
			{
				world->addLevelObject(new LevelObject(world->getObjectFromValue(valueAt(x, y, GREEN)), Vec3f(x*scale, heightAt(x, y), y*scale), Vec3f(0, rand() % 360, 0), 1, true));
			}
			if (valueAt(x, y, GREEN) == 180 || valueAt(x, y, GREEN) == 190 || valueAt(x, y, GREEN) == 170 || valueAt(x, y, GREEN) == 250)
			{
				world->addLevelObject(new LevelObject(world->getObjectFromValue(valueAt(x, y, GREEN)), Vec3f(x*scale, heightAt(x, y), y*scale), Vec3f(0, 0, 0), 1, true));
			}
			if ((valueAt(x, y, GREEN) >= 200) && (valueAt(x, y, GREEN) <= 240))
			{
				world->addLevelObject(new LevelObject(world->getObjectFromValue(valueAt(x, y, GREEN)), Vec3f(x*scale, heightAt(x, y), y*scale), Vec3f(0, 0, 0), 1, false));
			}

			Vec3f normal = ca.cross(ba);
			normal.Normalize();

			for (int i = 0; i < 4; i++)
			{
				float h = heightAt(x + offsets[i][0], y + offsets[i][1]);
				vertices.push_back(Vertex{ (float)(x + offsets[i][0])*scale, h*scale, (float)(y + offsets[i][1])*scale,
									normal.x, normal.y, normal.z,
									(x + offsets[i][0]) / (float)height, (y + offsets[i][1]) / (float)width } );
			}
		}
	}

	glGenTextures(1, &imageIndex);
	glBindTexture(GL_TEXTURE_2D, imageIndex);

	glTexImage2D(GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		width,				//width
		height,				//height
		0,					//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);			//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(imgData);
}

HeightMap::~HeightMap()
{
	glDeleteTextures(1, &imageIndex);
}

void HeightMap::Draw()
{
	glEnable(GL_LIGHTING);
	float color[] = { 0.7f, 0.7f, 0.7f, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, imageIndex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 6);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 3);
	glDrawArrays(GL_QUADS, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

float HeightMap::GetHeight(float x, float y)
{
	x /= scale;
	y /= scale;
	int ix = x;
	int iy = y;

	int index = (ix + (width - 1) * iy) * 4;

	Vertex& a = vertices[index];
	Vertex& b = vertices[index+1];
	Vertex& c = vertices[index+3];

	float lowervalue = ((b.z - c.z)*(a.x - c.x) + (c.x - b.x)*(a.z - c.z));
	float labda1 = ((b.z - c.z)*(x - c.x) + (c.x - b.x)*(y - c.z)) / lowervalue;
	float labda2 = ((c.y - a.y)*(x - c.x) + (a.x - c.x)*(y - c.y)) / lowervalue;
	float labda3 = 1 - labda1 - labda2;

	Vertex z = a * labda1 + b * labda2 + c * labda3;

	return z.y;
}

void HeightMap::SetTexture(const std::string &file)
{
	int bpp, width2, height2;
	unsigned char* imgData = stbi_load(file.c_str(), &width2, &height2, &bpp, 4);

	glBindTexture(GL_TEXTURE_2D, imageIndex);

	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width2,		//width
		height2,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(imgData);
}