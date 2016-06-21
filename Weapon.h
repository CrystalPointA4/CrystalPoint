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
    Weapon(std::string modelFilename, float scale, Vec3f location, Vec2f rotation,
           Vec3f offsetPlayer, Vec3f ankerPoint,
           Vec2f maxRotation, Vec2f minXRotation);
    ~Weapon();

    void draw();
    void rotateWeapon(Vec3f rotation);
    void rotate(Vec2f rotation);
    void move(Vec3f location);

    unsigned int damage;
    Model* weaponmodel;

    float scale;
    Vec3f position, rotation, rotationWeapon;
    Vec3f offsetPlayer, ankerPoint;
    Vec2f maxRotation, minRotation;
};


#endif //CRYSTALPOINT_WEAPON_H
