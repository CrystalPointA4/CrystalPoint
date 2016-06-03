#include "Entity.h"
#include "cmath"
#include <GL/freeglut.h>
#include "Model.h"


Entity::Entity()
{
	model = NULL;
	scale = 1;
	canCollide = true;
}


Entity::~Entity()
{
	if(model)
		Model::unload(model);
}


void Entity::draw()
{
	if (model)
	{
		glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glScalef(scale, scale, scale);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		model->draw();
		glCullFace(GL_FRONT);
		model->draw();
		glDisable(GL_CULL_FACE);

		glPopMatrix();
	}

}

bool Entity::inObject(const Vec3f & point)
{
	if (!model)
		return false;
	Vec3f center = position + model->center;
	float distance = ((point.x - center.x) * (point.x - center.x) + (point.z - center.z)*(point.z - center.z));
	if (distance < model->radius*scale*model->radius*scale)
		return true;
	return false;
}

