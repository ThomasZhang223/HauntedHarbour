#pragma once

#include "framework.h"
#include "GraphicsObject.h"
#include "WeaponsObject.h"
#include "PurpleBullet.h"

#define MOVE_RIGHT 1
#define MOVE_LEFT 2
#define STAND_RIGHT 3
#define STAND_LEFT 4
#define JUMP_RIGHT 5
#define JUMP_LEFT 6
#define SHOOT_RIGHT 7
#define SHOOT_LEFT 8

class PlayerObject : public WeaponsObject
{
public:
	int xSpeed, ySpeed;
	int state;

	bool bIsStoppedRight, bIsStoppedLeft;

	PlayerObject();
	~PlayerObject();

	void Move();
	
	void SetMoveRight();
	void SetMoveLeft();
	void SetStandRight();
	void SetStandLeft();
	void SetJumpRight();
	void SetJumpLeft();
	void SetShootRight();
	void SetShootLeft();
	
	void CheckCollisionWithBlock(GraphicsObject* block);
	void OnHit(BulletObject* projectile);

	bool IsJumping();
};

