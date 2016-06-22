//
// Created by janco on 25-5-16.
//

#ifndef CRYSTALPOINT_WEAPON_H
#define CRYSTALPOINT_WEAPON_H

#include "Vector.h"
#include "Model.h"
#include <string>

class Weapon {
public:
	enum Element {FIRE, WATER, EARTH, AIR};

    Weapon(std::string name, int damage, Element element, std::string modelFilename, float scale, Vec3f location, Vec2f rotation,
           Vec3f offsetPlayer, Vec3f ankerPoint,
           Vec2f maxRotation, Vec2f minXRotation,
		   Vec3f collision);
    ~Weapon();

    void draw();
    void rotateWeapon(Vec3f rotation);
    void rotate(Vec2f rotation);
    void move(Vec3f location);
	
	std::string name;
    unsigned int damage;
	Element element;

    Model* weaponmodel;

    float scale;
    Vec3f position, rotation, rotationWeapon;
    Vec3f offsetPlayer, ankerPoint, collision;
    Vec2f maxRotation, minRotation;
};


#endif //CRYSTALPOINT_WEAPON_H
