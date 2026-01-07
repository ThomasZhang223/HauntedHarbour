#pragma once

#include "GraphicsObject.h"


class BackgroundObject : public GraphicsObject
{
public:
	double scrollSpeed;

	BackgroundObject(CString fileName, int xPos, int yPos, int w, int h, double scrlSpd);
	~BackgroundObject();

	void Draw(HDC offScreenDC);
};

