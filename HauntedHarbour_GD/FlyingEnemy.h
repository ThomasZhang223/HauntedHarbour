#pragma once

#include "framework.h"
#include "EnemyObject.h"
#include "GreenBullet.h"
#include "PlayerObject.h"

#define _USE_MATH_DEFINES
#include <math.h>


class FlyingEnemy :
    public EnemyObject
{
public:
    int radius, angle;
    int centerX, centerY;
    int shootTick, shootDelay;

    PlayerObject* viktorRef;

    FlyingEnemy(PlayerObject* target, int cX, int cY);
    ~FlyingEnemy();

    void Move();
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithBlock(GraphicsObject* block);
    void Fire();
};

