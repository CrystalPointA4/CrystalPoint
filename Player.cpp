#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
#include <GL/freeglut.h>

#include <string>
#include <iostream>
#include <fstream>

Player* Player::instance = NULL;

Player::Player()
{
	speed = 10;
	maxHp = 100;
	health = maxHp;
	xp = 0;
	maxXp = 100;
	level = 1;
	crystals = 0;

	loadWeapons();

	currentleftweapon = 0;
	leftWeapon = leftweapons[0];
	leftWeapon->rotateWeapon(Vec3f(150, 0, 60));

	currentrightweapon = 0;
	rightWeapon = rightweapons[0];
	rightWeapon->rotateWeapon(Vec3f(150, 0, 60));
}

Player* Player::getInstance()
{
	if (instance == nullptr)
		instance = new Player();

	return instance;
}

void Player::init()
{
	instance = new Player();
}

Player::~Player()
{
	if (leftWeapon)
		delete leftWeapon;

	if (rightWeapon)
		delete rightWeapon;
}

void Player::setCamera()
{
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glTranslatef(-position.x, -position.y, -position.z);

	leftWeapon->rotate(rotation);
	rightWeapon->rotate(rotation);

}

void Player::setPosition(float angle, float fac, bool height)
{	
	if (height)
		position.y += angle*fac;
	else
	{
		position.x -= (float)cos((rotation.y + angle) / 180 * M_PI) * fac;
		position.z -= (float)sin((rotation.y + angle) / 180 * M_PI) * fac;
	}

	leftWeapon->move(position);
	rightWeapon->move(position);
}

void Player::draw() {
	leftWeapon->draw();
	rightWeapon->draw();
}

void Player::HpDown(int damage)
{
	int newHealth = health - damage;
	if (newHealth <= 0)
	{
		exit(0);
	}
	health = newHealth;
}

void Player::HpUp(int hp)
{
	if (health != maxHp)
	{
		int newHealth = health + hp;
		if (newHealth >= maxHp)
		{
			newHealth = maxHp;
		}
		health = newHealth;
	}	
}

void Player::XpUp(int xpUp)
{
	float newXp = xp + xpUp;
	if (newXp >= maxXp)
	{
		newXp -= maxXp;		
		levelUp();
	}
	xp = newXp;
}


void Player::levelUp()
{
	level++;
	maxXp += 50;
	maxHp += 10;
	health = maxHp;
}

void Player::loadWeapons()
{
	std::string fileName = "weapons.json";

	//Open world json file
	std::ifstream file(fileName);
	if (!file.is_open())
		std::cout << "Error, can't open world file - " << fileName << "\n";

	json::Value v = json::readJson(file);
	file.close();

	//Check file
	if (v["weapons"].isNull())
		std::cout << "Invalid weapons file: " << fileName << "\n";

	//Load object templates
	for (auto w : v["weapons"])
	{
		Weapon* lweapon;
		Weapon* rweapon;

		std::string name = w["name"].asString();
		std::string fileN = w["file"].asString();
		float damage = w["damage"].asFloat();

		Weapon::Element e = Weapon::FIRE;

		if(w["element"].asString() == "fire")
			e = Weapon::FIRE;
		else if (w["element"].asString() == "water")
			e = Weapon::WATER;
		else if (w["element"].asString() == "earth")
			e = Weapon::EARTH;
		else if (w["element"].asString() == "air")
			e = Weapon::AIR;
		else
			e = Weapon::FIRE;


		Vec3f leftoffset = Vec3f(w["left"]["offset"][0].asFloat(), w["left"]["offset"][1].asFloat(), w["left"]["offset"][2].asFloat());
		Vec3f rightoffset = Vec3f(w["right"]["offset"][0].asFloat(), w["right"]["offset"][1].asFloat(), w["right"]["offset"][2].asFloat());

		Vec3f anchor = Vec3f(w["anchor"][0].asFloat(), w["anchor"][1].asFloat(), w["anchor"][2].asFloat());
		Vec3f collision = Vec3f(w["collision"][0].asFloat(), w["collision"][1].asFloat(), w["collision"][2].asFloat());

		Vec2f maxRot = Vec2f(w["maxRotation"][0].asFloat(), w["maxRotation"][1].asFloat());
		Vec2f minRot = Vec2f(w["minRotation"][0].asFloat(), w["minRotation"][1].asFloat());

		lweapon = new Weapon(name, damage, e, fileN, 1, position, rotation, leftoffset, anchor, maxRot, minRot, collision);
		rweapon = new Weapon(name, damage, e, fileN, 1, position, rotation, rightoffset, anchor, maxRot, minRot, collision);

		leftweapons.push_back(lweapon);
		rightweapons.push_back(rweapon);
	}
	
}

void Player::PreviousRightWeapon()
{
	currentrightweapon--;

	if (currentrightweapon < 0)
		currentrightweapon = (rightweapons.size() > level ? level - 1 : rightweapons.size() - 1);

	rightWeapon = rightweapons[currentrightweapon];
}
void Player::NextRightWeapon(void)
{
	currentrightweapon++;

	if (currentrightweapon > level - 1 || currentrightweapon > rightweapons.size() - 1)
		currentrightweapon = 0;

	rightWeapon = rightweapons[currentrightweapon];
}
void Player::PreviousLeftWeapon(void)
{
	currentleftweapon--;

	if (currentleftweapon < 0)
		currentleftweapon = (leftweapons.size() > level ? level - 1 : leftweapons.size() - 1);

	leftWeapon = leftweapons[currentleftweapon];
}
void Player::NextLeftWeapon(void)
{
	currentleftweapon++;

	if (currentleftweapon > level - 1 || currentleftweapon > leftweapons.size() - 1)
		currentleftweapon = 0;

	leftWeapon = leftweapons[currentleftweapon];
}