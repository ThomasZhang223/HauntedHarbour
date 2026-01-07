#include "FlyingEnemy.h"


FlyingEnemy::FlyingEnemy(PlayerObject* target, int cX, int cY) :
	EnemyObject("../pics/SeaHag.bmp", 200, 200)
{
	viktorRef = target;

	currentHealth = 50;
	maxHealth = 50;

	width = 28;
	height = 39;

	hitWidth = width;
	hitHeight = height;

	currentCell = 0;
	startCell = 0;
	endCell = 4;

	bIsLooping = true;

	xSpeed = -5;
	ySpeed = 0;

	radius = 20;
	centerX = cX;
	centerY = cY;
	angle = 0;

	shootDelay = 30;
	shootTick = 0;

	numBullets = 20;

	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet(20);
		bullets[i]->maxDistance = 400;
	}
}

FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::Move()
{
	if (this->bIsAlive == true)
	{
		double _radians = (double)angle / 180 * M_PI;

		xPos = centerX + radius * cos(_radians);
		yPos = centerY + radius * sin(_radians);

		angle += 10;

		shootTick++;

		if (shootTick == shootDelay)
		{
			Fire();
			shootTick = 0;
		}
	}

	Animate();
}

void FlyingEnemy::OnHit(BulletObject* projectile)
{
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		currentCell = 0;
		startCell = 0;
		endCell = 6;

		width = 32;
		height = 28;

		picX = 0;
		picY = 156;

		bIsLooping = false;
		bIsAlive = false;
	}
}

void FlyingEnemy::CheckCollisionWithBlock(GraphicsObject* block)
{
}

void FlyingEnemy::Fire()
{
	double _xDistance = abs((this->xPos + this->width / 2) - (viktorRef->xPos + viktorRef->width / 2)); // run
	double _yDistance = abs((this->yPos + this->height) - (viktorRef->yPos + viktorRef->height / 2)); // rise

	int _xSide = 1; // right by default
	int _ySide = 1; // down by default

	if (viktorRef->xPos < this->xPos)
		_xSide = -1;
	if (viktorRef->yPos < this->yPos)
		_ySide = -1;

	if (_xDistance > _yDistance)
	{
		FireBullets(
			xPos + width / 2,
			yPos + height,
			10 * _xSide,
			10 * _yDistance / _xDistance * _ySide);
	}
	else
	{
		FireBullets(
			xPos + width / 2,
			yPos + height,
			10 * _xDistance / _yDistance * _xSide,
			10 * _ySide);
	}
}
