#pragma once

#include "framework.h"
#include "WeaponsObject.h"


class EnemyObject :
    public WeaponsObject
{
public:
    int xSpeed, ySpeed;
    bool bIsAlive;

    EnemyObject(CString fileName, int xPos, int yPos) :
        WeaponsObject(fileName, xPos, yPos)
    {
        xSpeed = 0;
        ySpeed = 0;

        bIsAlive = true;
    }

    ~EnemyObject()
    {}

    virtual void Move() = 0;
    virtual void OnHit(BulletObject* projectile) = 0;
    virtual void CheckCollisionWithBlock(GraphicsObject* block) = 0;
};

