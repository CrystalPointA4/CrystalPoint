#pragma once

#include <GL/freeglut.h>
#include <list>
#include <vector>
#include <map>
#include "Vector.h"
#include "Vertex.h"

class Model
{
private:
	
	class VertexIndex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<VertexIndex> vertices;
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
		std::list<Face> faces;
		std::vector<Vertex> VertexArray;
	};

	std::vector<Vec3f>	vertices;
	std::vector<Vec3f>	normals;
	std::vector<Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(std::string fileName, std::string dirName);

	Model(std::string filename);
	~Model(void);

	public:

	static std::map<std::string, std::pair<Model*, int> > cache;
	static Model* load(const std::string &fileName);
	static void unload(Model* model);

	void draw();
	void Optimise(ObjGroup *t);

	Vec3f minVertex;
	Vec3f maxVertex;

	Vec3f center;
	float radius;
};
