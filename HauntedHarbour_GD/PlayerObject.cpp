#include "PlayerObject.h"


PlayerObject::PlayerObject() : WeaponsObject("../pics/ViktorTesla.bmp", 100, 100)
{
	currentHealth = 100;
	maxHealth = 100;

	SetStandRight();

	xSpeed = 0;
	ySpeed = 0;

	hitWidth = 54;
	hitHeight = 42;

	numBullets = 10;

	// Create a bullet for each bullet fired
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new PurpleBullet(30);
	}
}

PlayerObject::~PlayerObject()
{
	// No implementation
}

void PlayerObject::Move()
{
	// Set the previous position to the current position before hitting an obstacle
	prevX = xPos;
	prevY = yPos;

	xPos += xSpeed;
	yPos += ySpeed;

	ySpeed += GRAVITY;

	// if Viktor's sprite box is at the ground
	if (yPos > GROUND - height)
	{
		if (state == JUMP_RIGHT && bIsStoppedRight == true)
		{
			SetStandRight();
		}
		else if (state == JUMP_RIGHT && bIsStoppedRight == false)
		{
			SetMoveRight();
		}
		else if (state == JUMP_LEFT && bIsStoppedLeft == true)
		{
			SetStandLeft();
		}
		else if (state == JUMP_LEFT && bIsStoppedLeft == false)
		{
			SetMoveLeft();
		}

		// stay at the ground
		yPos = GROUND - height;

		// stop falling (or flying)
		ySpeed = 0;
	}

	if ((xPos - mapPosition < 100 && xSpeed < 0) || (xPos - mapPosition > 350 && xSpeed > 0))
	{
		mapPosition += xSpeed;
	}

	Animate();
}

void PlayerObject::SetMoveRight()
{
	width = 54;
	height = 42;
	picX = 60;
	picY = 0;
	//currentCell = 0;
	startCell = 1;
	endCell = 9;
	bIsLooping = true;
	xSpeed = 10;
	//ySpeed = ySpeed;
	state = MOVE_RIGHT;
}

void PlayerObject::SetMoveLeft()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 42; //y position in the sprite strip
	//currentCell = 0;
	startCell = 1;
	endCell = 9;
	bIsLooping = true;
	xSpeed = -10;
	// ySpeed = ySpeed;
	state = MOVE_LEFT;
}

void PlayerObject::SetStandRight()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 0; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bIsLooping = false;
	xSpeed = 0;
	// ySpeed = ySpeed;
	state = STAND_RIGHT;
}

void PlayerObject::SetStandLeft()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 42; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bIsLooping = false;
	xSpeed = 0;
	//ySpeed = ySpeed;
	state = STAND_LEFT;
}

void PlayerObject::SetJumpRight()
{
	width = 48;
	height = 56;
	picX = 0;
	picY = 86; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 5;
	bIsLooping = false;
	//xSpeed = -10;
	ySpeed = -30;
	state = JUMP_RIGHT;
}

void PlayerObject::SetJumpLeft()
{
	width = 48;
	height = 56;
	picX = 0;
	picY = 146; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 5;
	bIsLooping = false;
	//xSpeed = -10;
	ySpeed = -30;
	state = JUMP_LEFT;
}

void PlayerObject::SetShootRight()
{
	width = 60;
	height = 38;
	picX = 0;
	picY = 199; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bIsLooping = false;
	xSpeed = 0;
	//ySpeed = -30;
	state = SHOOT_RIGHT;
}

void PlayerObject::SetShootLeft()
{
	width = 60;
	height = 38;
	picX = 0;
	picY = 237; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bIsLooping = false;
	xSpeed = 0;
	//ySpeed = -30;
	state = SHOOT_LEFT;
}

void PlayerObject::CheckCollisionWithBlock(GraphicsObject* block)
{
	if (this->IsColliding(block) == true)
	{
		// from the left side of the obstacle
		if (this->prevX + this->hitWidth <= block->xPos)
		{
			// "push" player back to the left
			this->xPos = block->xPos - this->hitWidth;
		}
		// from the right side of the obstacle
		else if (this->prevX >= block->xPos + block->hitWidth)
		{
			// "push" to the right
			this->xPos = block->xPos + block->hitWidth;
		}
		// from the top side of the obstacle
		else if (this->prevY + this->hitHeight <= block->yPos)
		{
			if (state == JUMP_RIGHT && bIsStoppedRight == true)
			{
				SetStandRight();
			}
			else if (state == JUMP_RIGHT && bIsStoppedRight == false)
			{
				SetMoveRight();
			}
			else if (state == JUMP_LEFT && bIsStoppedLeft == true)
			{
				SetStandLeft();
			}
			else if (state == JUMP_LEFT && bIsStoppedLeft == false)
			{
				SetMoveLeft();
			}

			this->yPos = block->yPos - this->hitHeight;
			this->ySpeed = 0;
		}
		// from the bottom side of the obstacle
		else if (this->prevY >= block->yPos + block->hitHeight)
		{
			// "push" down
			this->yPos = block->yPos + block->hitHeight + 1;
			this->ySpeed = 0;
		}
	}
}

void PlayerObject::OnHit(BulletObject* projectile)
{
	this->xPos += projectile->xSpeed;
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		xPos = 100;
		yPos = 100;

		mapPosition = 0;

		xSpeed = 0;
		ySpeed = 0;

		SetStandRight();

		currentHealth = maxHealth;
	}
}

bool PlayerObject::IsJumping()
{
	return (state == JUMP_RIGHT || state == JUMP_LEFT);
}