#include "PurpleBullet.h"

PurpleBullet::PurpleBullet(int dmg) : BulletObject("../Pics/PurpleFire.bmp")
{
	width = 12;
	height = 12;

	hitWidth = width;
	hitHeight = height;

	this->damage = dmg;
}

PurpleBullet::~PurpleBullet()
{
}

void PurpleBullet::SetExplode()
{
	// move the selected sprite
	// to the exploding one from the spritesheet
	picX = 0;
	picY = 12;

	// set the size from the small bullet
	// to the bigger explosion
	width = 32;
	height = 32;

	// move the position to center it to the original bullet
	xPos -= 12;
	yPos -= 12;

	bIsLooping = false;

	// set the sprite to be #2 in the spritesheet
	endCell = 2;
	currentCell = 0;

	bIsExploding = true;
}

void PurpleBullet::ResetBullet()
{
	bIsExploding = false;
	bIsFired = false;

	currentCell = 0;
	endCell = 0;

	// back to the origin of the spritesheet
	// so we see the bullet next time we shoot this bullet
	picX = 0;
	picY = 0;

	width = 12;
	height = 12;

	distanceTravelled = 0;
}