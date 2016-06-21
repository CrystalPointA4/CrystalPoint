//
// Created by janco on 25-5-16.
//

#include "Weapon.h"
#include "Model.h"
#include <iostream>
#include <string>
#include <cmath>


Weapon::Weapon(std::string modelFilename, float scale, Vec3f location, Vec2f rotation,
               Vec3f offsetPlayer, Vec3f ankerPoint, Vec3f collisionPoint,
               Vec2f maxRotation, Vec2f minRotation){
    weaponmodel = Model::load(modelFilename);
    rotate(rotation);
    move(location);
    this->scale = scale;

    this->offsetPlayer = offsetPlayer;
    this->ankerPoint = ankerPoint;
    this->maxRotation = maxRotation;
    this->minRotation = minRotation;
    this->collisionPoint = collisionPoint;
};

Weapon::~Weapon(){

}

void Weapon::rotateWeapon(Vec3f rotation){
    if(rotation.x < maxRotation.x && rotation.x > minRotation.x){
        rotationWeapon.x = rotation.x;
    }
    if(rotation.z < maxRotation.y && rotation.z > minRotation.y){
        rotationWeapon.z = rotation.z;
    }
    rotationWeapon.y = rotation.y;
}

void Weapon::rotate(Vec2f rotation){
    this->rotation.y = -rotation.y;
}

void Weapon::move(Vec3f location){
    position = location;
}

void Weapon::draw(){
    if (weaponmodel != nullptr)
    {
        glPushMatrix();

        //Player position and rotation
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1, 0, 0);
        glRotatef(rotation.y, 0, 1, 0);
        glRotatef(rotation.z, 0, 0, 1);

        //offset from player
        glTranslatef(offsetPlayer.x, offsetPlayer.y, offsetPlayer.z);

        //Rotate weapon itself, from specific anker point
        glTranslatef(ankerPoint.x, ankerPoint.y, ankerPoint.z);
        glRotatef(rotationWeapon.z, 0, 0, 1);
        glRotatef(rotationWeapon.y, 0, 1, 0);
        glRotatef(rotationWeapon.x, 1, 0, 0);
        glTranslatef(-ankerPoint.x, -ankerPoint.y, -ankerPoint.z);

        glScalef(scale, scale, scale);

        weaponmodel->draw();

        //Test code for finding anker point
        glColor3ub(255, 255, 0);
        glTranslatef(collisionPoint.x, collisionPoint.y, collisionPoint.z);
        glBegin(GL_LINES);
        glVertex2f(0, 4);
        glVertex2f(0, -4);
        glVertex2f(4, 0);
        glVertex2f(-4, 0);
        glEnd();

        glPopMatrix();

    }
}
