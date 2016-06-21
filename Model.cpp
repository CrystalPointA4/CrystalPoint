#include "Model.h"

#include "stb_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

//Prototypes
std::vector<std::string> split(std::string str, std::string sep);
std::string replace(std::string str, std::string toReplace, std::string replacement);
std::string toLower(std::string data);

Model::Model(std::string fileName)
{
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if (line == "")
			continue;
		if (line[0] == ' ')
			line = line.substr(1);
		if (line == "")
			continue;
		if (line[line.length() - 1] == ' ')
			line = line.substr(0, line.length() - 1);
		if (line == "")
			continue;
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					VertexIndex vertex;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2)		//alleen texture
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)		//v/t/n of v//n
					{
						if (indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{//smoothing
		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	groups.push_back(currentGroup);

	minVertex = vertices[0];
	maxVertex = vertices[0];
	for (auto v : vertices)
	{
		for (int i = 0; i < 3; i++)
		{
			minVertex[i] = fmin(minVertex[i], v[i]);
			maxVertex[i] = fmax(maxVertex[i], v[i]);
		}
	}
	center = (minVertex + maxVertex) / 2.0f;
	radius = 0;
	for (auto v : vertices)
		radius = fmax(radius, (center.x - v.x) * (center.x - v.x) + (center.z - v.z) * (center.z - v.z));
	radius = sqrt(radius);

	for (ObjGroup *group : groups)
	{
		Optimise(group);
	}
}

void Model::Optimise(ObjGroup *t)
{
	for (Face &face : t->faces)
	{
		for (auto &vertex : face.vertices)
		{
			t->VertexArray.push_back(Vertex(vertices[vertex.position].x, vertices[vertex.position].y, vertices[vertex.position].z,
				normals[vertex.normal].x, normals[vertex.normal].y, normals[vertex.normal].z,
				texcoords[vertex.texcoord].x, texcoords[vertex.texcoord].y));

		}
	}
}

void Model::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	for (auto &g : groups)
	{
		if (materials[g->materialIndex]->hasTexture)
		{
			glEnable(GL_TEXTURE_2D);
			materials[g->materialIndex]->texture->bind();
		}
		else
		{
			glDisable(GL_TEXTURE_2D);

			float color[4] = { 1, 0, 0, 1 };

			if (materials[g->materialIndex]->hasDiffuse)
			{
				memcpy(color, materials[g->materialIndex]->diffuseColor.v, 3 * sizeof(float));
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
			}
			else if (materials[g->materialIndex]->hasAmbient)
			{
				memcpy(color, materials[g->materialIndex]->ambientColor.v, 3 * sizeof(float));
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
			}
			else if (materials[g->materialIndex]->hasSpecular)
			{
				memcpy(color, materials[g->materialIndex]->specularColor.v, 3 * sizeof(float));
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
			}
		}

		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), ((float*)g->VertexArray.data()) + 0);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), ((float*)g->VertexArray.data()) + 3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), ((float*)g->VertexArray.data()) + 6);
		glDrawArrays(GL_TRIANGLES, 0, g->VertexArray.size());
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Model::loadMaterialFile(std::string fileName, std::string dirName)
{
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if (line == "")
			continue;
		if (line[0] == ' ')
			line = line.substr(1);
		if (line == "")
			continue;
		if (line[line.length() - 1] == ' ')
			line = line.substr(0, line.length() - 1);
		if (line == "")
			continue;
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			currentMaterial->hasTexture = true;
			currentMaterial->texture = new Texture(dirName + "/" + params[1]);
		}
		else if (params[0] == "kd")
		{
			currentMaterial->hasDiffuse = true;
			currentMaterial->diffuseColor = Vec3f(atof(params[1].c_str()), atof(params[2].c_str()), atof(params[3].c_str()));
		}
		else if (params[0] == "ka")
		{
			currentMaterial->hasAmbient = true;
			currentMaterial->ambientColor = Vec3f(atof(params[1].c_str()), atof(params[2].c_str()), atof(params[3].c_str()));
		}
		else if (params[0] == "ks")
		{
			currentMaterial->hasSpecular = true;
			currentMaterial->specularColor = Vec3f(atof(params[1].c_str()), atof(params[2].c_str()), atof(params[3].c_str()));
		}
		else
			std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

Model::MaterialInfo::MaterialInfo()
{
	hasTexture = false;
}

Model::Texture::Texture(const std::string & fileName)
{
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);

	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	stbi_image_free(imgData);
}

void Model::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, index);
}

std::string replace(std::string str, std::string toReplace, std::string replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

std::vector<std::string> split(std::string str, std::string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(sep);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}



std::map<std::string, std::pair<Model*, int>> Model::cache;

Model* Model::load(const std::string &fileName)
{
	if (cache.find(fileName) == cache.end())
		cache[fileName] = std::pair<Model*, int>(new Model(fileName), 0);
	cache[fileName].second++;
	return cache[fileName].first;
}

void Model::unload(Model* model)
{
	for (auto m : cache)
	{
		if (m.second.first == model)
		{
			m.second.second--;
			if (m.second.second == 0)
			{
				delete m.second.first;
				cache.erase(cache.find(m.first));
				break;
			}

		}
	}
}

Model::~Model(void)
{

}