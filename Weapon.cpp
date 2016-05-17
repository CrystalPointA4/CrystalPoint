#include "Weapon.h"

Weapon::Weapon(const string &filename)
{
	weaponModel = new Model(filename);
}

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

void Weapon::draw_weapon(void)
{
	
	if (weaponModel != nullptr)
	{				
		glScalef(scale,scale,scale);
		glRotatef(rotX, 1, 0, 0);
		weaponModel->draw();		
	}		
}


