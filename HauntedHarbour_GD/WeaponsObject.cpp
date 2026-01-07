#include "WeaponsObject.h"

WeaponsObject::WeaponsObject(CString fileName, int xPos, int yPos) : GraphicsObject(fileName, xPos, yPos)
{

}

WeaponsObject::~WeaponsObject()
{

}

void WeaponsObject::FireBullets(int xPos, int yPos, int xSpeed, int ySpeed)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == false)
		{
			bullets[i]->xPos = xPos;
			bullets[i]->yPos = yPos;
			bullets[i]->xSpeed = xSpeed;
			bullets[i]->ySpeed = ySpeed;
			
			bullets[i]->bIsFired = true;
			bullets[i]->distanceTravelled = 0;

			// We might not fire all the bullets at once,
			// so leave the loop in this case
			break;
		}
	}
}

void WeaponsObject::DrawBullets(HDC offScreenDC)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == true)
		{
			bullets[i]->Draw(offScreenDC);
		}
	}
}

void WeaponsObject::MoveBullets()
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == true)
		{
			bullets[i]->Move();
		}
	}
}

void WeaponsObject::CheckBulletCollisionWithBlock(GraphicsObject* block)
{
	// Check each bullet (from the first that was fired, up to the last being fired)
	for (int i = 0; i < numBullets; i++)
	{
		// Only check the bullets that have been fired, so skip the rest (up to 10) that weren't fired
		if (bullets[i]->bIsFired == true)
		{
			// if any bullet that was fired hits the block
			if (bullets[i]->IsColliding(block) == true && bullets[i]->bIsExploding == false)
			{
				// adjust the exploding bullet position upon collision
				// if firing from the left
				if (abs(bullets[i]->xPos - block->xPos) < abs(bullets[i]->xPos - (block->xPos + block->width)))
				{
					bullets[i]->xPos = block->xPos;
				}
				// if firing from the right
				else if (abs(bullets[i]->xPos - block->xPos) > abs(bullets[i]->xPos - (block->xPos + block->width)))
				{
					bullets[i]->xPos = block->xPos + block->width;
				}

				bullets[i]->SetExplode();
			}
		}
	}
}

void WeaponsObject::CheckBulletCollisionWithEntity(WeaponsObject* entity)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == true && bullets[i]->bIsExploding == false)
		{
			if (bullets[i]->IsColliding(entity) == true)
			{
				entity->OnHit(bullets[i]);
				bullets[i]->SetExplode();
			}
		}
	}
}

