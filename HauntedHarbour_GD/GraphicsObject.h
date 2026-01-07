#pragma once

#include "framework.h"


class GraphicsObject
{
public:
	CString ID;
	CImage image;
	
	int width, height;
	int xPos, yPos;
	int picX, picY;
	int currentCell, startCell, endCell;
	int hitWidth, hitHeight;		// Collision box

	bool bIsLooping;

	GraphicsObject(CString fileName, int xPos, int yPos, int w = 55, int h = 42);
	~GraphicsObject();

	void Draw(HDC offScreenDC);
	void Animate();

	bool IsColliding(GraphicsObject* entity);
};

