#include "Entity.h"

#include <GL/freeglut.h>

#include "Model.h"


Entity::Entity()
{
	model = NULL;
}


Entity::~Entity()
{
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

		model->draw();
		glPopMatrix();
	}

}

