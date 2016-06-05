#include "LevelObject.h"

#include "Model.h"


LevelObject::LevelObject(const std::string &fileName, const Vec3f &position, const Vec3f &rotation, const float &scale, const bool &hasCollision)
{
	model = Model::load(fileName);
	this->position = position;
	this->position.x -= model->center.x;
	this->position.z -= model->center.z;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = hasCollision;
}


LevelObject::~LevelObject()
{
	if (model)
		Model::unload(model);
}
