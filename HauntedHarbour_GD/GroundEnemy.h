#pragma once

#include "WeaponsObject.h"
#include "GreenBullet.h"
#include "EnemyObject.h"


class GroundEnemy :
    public EnemyObject
{
public:
    GroundEnemy();
    ~GroundEnemy();

    void Move();
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithBlock(GraphicsObject* block);
};

