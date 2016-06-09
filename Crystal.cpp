#include "Crystal.h"
#include "Model.h"


Crystal::Crystal(const std::string &fileName, const Vec3f &position, Vec3f &rotation, const float &scale)
{
	model = Model::load(fileName);
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = true;
	filled = true;
}


Crystal::~Crystal()
{
	if (model)
		Model::unload(model);
}

void Crystal::draw()
{
	if (filled)
		Entity::draw();	
}
