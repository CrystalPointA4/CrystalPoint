#include "HeightMap.h"
#include "stb_image.h"

#include <GL/freeglut.h>
#include <iostream>
#include <string>


HeightMap::HeightMap(const std::string &file)
{
	int bpp;
	unsigned char* imgData = stbi_load(file.c_str(), &width, &height, &bpp, 4);

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			int offsets[4][2] = { { 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 } };
			for (int i = 0; i < 4; i++)
			{
				float y = ((float)imgData[((h + offsets[i][0]) + (w + offsets[i][1]) * width) * 4]);
				y = (y / 256.0f) * 100.0f;

				vertices.push_back(Vertex{ (float)(h + offsets[i][0])*scale, y*scale, (float)(w + offsets[i][1])*scale,
									0, 1, 0,
									(h + offsets[i][0]) / (float)height, (w + offsets[i][1]) / (float)width } );
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
}

void HeightMap::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, imageIndex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 6);
	//glNormalPointer(GL_FLOAT, sizeof(Vertex), ((float*)cubeVertices.data()) + 3);
	glDrawArrays(GL_QUADS, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
}

void HeightMap::GetHeigth(float x, float z)
{

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