#pragma once

#include "GraphicsObject.h"
#include "BulletObject.h"


class WeaponsObject :
    public GraphicsObject
{
public:
    int numBullets;
    int prevX, prevY;
    int currentHealth, maxHealth;

    BulletObject* bullets[50];

    WeaponsObject(CString fileName, int xPos, int yPos);
    ~WeaponsObject();

    void FireBullets(int xPos, int yPos, int xSpeed, int ySpeed);
    void DrawBullets(HDC offScreenDC);
    void MoveBullets();
    void CheckBulletCollisionWithBlock(GraphicsObject* block);
    void CheckBulletCollisionWithEntity(WeaponsObject* entity);

    virtual void OnHit(BulletObject* projectile) {};
};

