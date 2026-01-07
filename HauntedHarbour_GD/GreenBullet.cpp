#include "GreenBullet.h"

GreenBullet::GreenBullet(int dmg) : BulletObject("../pics/GreenFire.bmp")
{
	width = 7;
	height = 7;

	hitWidth = width;
	hitHeight = height;

	this->damage = dmg;
}

GreenBullet::~GreenBullet()
{
}

void GreenBullet::SetExplode()
{
	// move the selected sprite
	// to the exploding one from the spritesheet
	picX = 0;
	picY = 8;

	// set the size from the small bullet
	// to the bigger explosion
	width = 15;
	height = 15;

	// move the position to center it to the original bullet
	xPos -= 8;
	yPos -= 8;

	bIsLooping = false;

	// set the sprite to be #2 in the spritesheet
	endCell = 2;
	currentCell = 0;

	bIsExploding = true;
}

void GreenBullet::ResetBullet()
{
	bIsExploding = false;
	bIsFired = false;

	currentCell = 0;
	endCell = 0;

	// back to the origin of the spritesheet
	// so we see the bullet next time we shoot this bullet
	picX = 0;
	picY = 0;

	width = 7;
	height = 7;

	distanceTravelled = 0;
}