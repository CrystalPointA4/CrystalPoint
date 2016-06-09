#include "Crystal.h"
#include "Model.h"


Crystal::Crystal(const std::string & filled, const std::string & empty, const Vec3f & position, Vec3f & rotation, const float & scale)
{
	this->filled = filled;
	this->empty = empty;

	model = Model::load(this->filled);
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = true;
	isFilled = true;
}

Crystal::~Crystal()
{
	if (model)
		Model::unload(model);
}

void Crystal::draw()
{	
	Entity::draw();	
}

void Crystal::pickUp()
{
	isFilled = false;
	model = Model::load(empty);
}
