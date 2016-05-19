#include "WorldState.h"
#include "Player.h"



WorldState::WorldState()
{
	/*player = Player::GetInstance();*/
}


WorldState::~WorldState()
{
	//if (player != nullptr)
		//delete player;
}

void WorldState::Keyboard(bool keys[255],float deltaTime)
{
	float speed = 10;
	std::cout << "Keyboard doet het in de world state" << std::endl;
	/*if (keys['a']) player->PlayerMoveEyes(0, deltaTime*speed, false);
	if (keys['d']) player->PlayerMoveEyes(180, deltaTime*speed, false);
	if (keys['w']) player->PlayerMoveEyes(90, deltaTime*speed, false);
	if (keys['s']) player->PlayerMoveEyes(270, deltaTime*speed, false);
	if (keys['q']) player->PlayerMoveEyes(1, deltaTime*speed, true);
	if (keys['e']) player->PlayerMoveEyes(-1, deltaTime*speed, true);	*/

	if (keys['a']) Player::GetInstance().PlayerMoveEyes(0, deltaTime*speed, false);
	if (keys['d']) Player::GetInstance().PlayerMoveEyes(180, deltaTime*speed, false);
	if (keys['w']) Player::GetInstance().PlayerMoveEyes(90, deltaTime*speed, false);
	if (keys['s']) Player::GetInstance().PlayerMoveEyes(270, deltaTime*speed, false);
	if (keys['q']) Player::GetInstance().PlayerMoveEyes(1, deltaTime*speed, true);
	if (keys['e']) Player::GetInstance().PlayerMoveEyes(-1, deltaTime*speed, true);	
}

void WorldState::MouseMove(int x, int y, int dx, int dy)
{
	//player->PlayerRotateEyes(dx, dy);
	Player::GetInstance().PlayerRotateEyes(dx, dy);
}

void WorldState::Display()
{
	Player::GetInstance().Display();

	glutSolidCube(10.0);
}

