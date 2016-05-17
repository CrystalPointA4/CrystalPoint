#pragma once
#include "Header.h"
#include "ModelInstance.h"

class Model
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		list<Vertex> vertices;
	};

	class Texture
	{
		GLuint index;
	public:
		Texture(const std::string &fileName);
		void bind();
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
		bool hasTexture;

		bool hasDiffuse;
		Vec3f diffuseColor;
		bool hasAmbient;
		Vec3f ambientColor;
		bool hasSpecular;
		Vec3f specularColor;

	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		list<Face> faces;
	};

	std::vector<Vec3f>	vertices;
	std::vector<Vec3f>	normals;
	std::vector<Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	std::vector<ModelInstance*> instances;

	void loadMaterialFile(std::string fileName, std::string dirName);
public:
	Model(std::string filename);
	Model(void);
	~Model(void);

	void AddInstance(ModelInstance* inst);

	void draw();
};
