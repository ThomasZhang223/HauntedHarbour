#include "GroundEnemy.h"


GroundEnemy::GroundEnemy() : EnemyObject("../Pics/SkullCrab.bmp", 200, 200)
{
	width = 28;
	height = 35;

	hitWidth = width;
	hitHeight = height;

	xSpeed = 5;

	currentCell = 0;
	startCell = 0;
	endCell = 10;

	picY = 35;

	bIsLooping = true;

	numBullets = 5;

	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet(20);
	}

	bIsAlive = true;
}

GroundEnemy::~GroundEnemy()
{
}

void GroundEnemy::Move()
{
	prevX = xPos;
	prevY = yPos;

	xPos += xSpeed;
	yPos += ySpeed;

	ySpeed += GRAVITY;

	// if the enemy goes past the ground
	if (yPos > GROUND - height)
	{
		yPos = GROUND - height;
		ySpeed = 0;
	}

	if (bIsAlive == true)
	{
		int _randNum = rand() % 30;

		if (_randNum == 1)
		{
			// if moving left
			if (this->xSpeed < 0)
			{
				FireBullets(xPos + 10, yPos + 20, -10, 0);
			}
			// if moving right
			else
			{
				FireBullets(xPos + 10, yPos + 20, 10, 0);
			}
		}
	}

	Animate();
}

void GroundEnemy::OnHit(BulletObject* projectile)
{
	this->xPos += projectile->xSpeed;

	currentCell = 0;
	endCell = 0;

	if (this->xSpeed < 0)
	{
		picY = 70;
	}
	else
	{
		picY = 105;
	}

	bIsAlive = false;
	xSpeed = 0;
}

void GroundEnemy::CheckCollisionWithBlock(GraphicsObject* block)
{
	if (this->IsColliding(block) == true)
	{
		// from the left side of the obstacle
		if (this->prevX + this->hitWidth <= block->xPos)
		{
			// invert the direction
			xSpeed *= -1;
			this->xPos = block->xPos - this->hitWidth;
			picY = 0;
		}
		// from the right side of the obstacle
		else if (this->prevX >= block->xPos + block->hitWidth)
		{
			xSpeed *= -1;
			this->xPos = block->xPos + block->hitWidth;
			picY = 35;
		}
		// from the top side of the obstacle
		else if (this->prevY + this->hitHeight <= block->yPos)
		{
			ySpeed = 0;
			this->yPos = block->yPos - this->hitHeight;
		}
		// from the bottom side of the obstacle
		else if (this->prevY >= block->yPos + block->hitHeight)
		{
			ySpeed = 0;
			this->yPos = block->yPos + block->hitHeight;
		}
	}
}
