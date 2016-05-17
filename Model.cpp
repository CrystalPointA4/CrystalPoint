#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Prototypes
vector<string> split(string str, string sep);
string replace(string str, string toReplace, string replacement);
string toLower(string data);

Model::Model(string fileName)
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
					Vertex vertex;
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
}

Model::Model(void)
{
	Model("models/TextureZwaard.obj");
}

Model::~Model(void)
{
}

void Model::AddInstance(ModelInstance* inst)
{
	instances.push_back(inst);
}

void Model::draw()
{
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

		for (auto &instance : instances)
		{

			glBegin(GL_TRIANGLES);
			for (auto &f : g->faces)
			{
				for (auto &v : f.vertices)
				{
					glPushMatrix();

					glTranslatef(instance->translation.x, instance->translation.y, instance->translation.z);
					glRotatef(instance->rotation.x, 1, 0, 0);
					glRotatef(instance->rotation.y, 0, 1, 0);
					glRotatef(instance->rotation.z, 0, 0, 1);
					glScalef(instance->scale.x, instance->scale.y, instance->scale.z);

					glNormal3f(normals[v.normal].x, normals[v.normal].y, normals[v.normal].z);
					glTexCoord2f(texcoords[v.texcoord].x, texcoords[v.texcoord].y);
					glVertex3f(vertices[v.position].x, vertices[v.position].y, vertices[v.position].z);
				}
			}
			glEnd();

		}
	}
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
	Texture *texture;
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
	stbi_image_free(imgData);
}

void Model::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, index);
}

string replace(string str, string toReplace, string replacement)
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

vector<string> split(string str, string sep)
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

inline string toLower(string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}
