#include "framework.h"
#include "BulletObject.h"


BulletObject::BulletObject(CString fileName) : GraphicsObject(fileName, 0, 0)
{
	bIsFired = false;
	width = 12;
	height = 12;
	hitWidth = width;
	hitHeight = height;
	distanceTravelled = 0;
	maxDistance = 300;
	xSpeed = 0;
	ySpeed = 0;
	bIsExploding = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::Move()
{
	Animate();

	if (bIsExploding == true)
	{
		if (currentCell == endCell)
		{
			ResetBullet();
		}
	}
	else
	{
		xPos += xSpeed;
		yPos += ySpeed;

		distanceTravelled += abs(xSpeed) + abs(ySpeed);

		if (distanceTravelled > maxDistance)
		{
			bIsFired = false;
			distanceTravelled = 0;
		}
	}
}
