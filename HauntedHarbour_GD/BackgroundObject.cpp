#include "BackgroundObject.h"


BackgroundObject::BackgroundObject(CString fileName, int xPos, int yPos, int w, int h, double scrlSpd) : GraphicsObject(fileName, xPos, yPos, w, h)
{
	width = w;
	height = h;
	scrollSpeed = scrlSpd;
}

BackgroundObject::~BackgroundObject()
{

}

void BackgroundObject::Draw(HDC offScreenDC)
{
	CImage _image;

	// % get remainder of result
	int _relativeX = (int)((xPos - mapPosition) * scrollSpeed) % width;

	_image.Load(ID);

	// Set the pink color to be used as a transparency channel
	_image.SetTransparentColor(RGB(255, 174, 201));

	// Draw on the screen
	// Center background
	_image.TransparentBlt(offScreenDC, _relativeX, yPos, width, height, 0, 0, width, height);
	// Right background
	_image.TransparentBlt(offScreenDC, _relativeX + width, yPos, width, height, 0, 0, width, height);
	// Left background
	_image.TransparentBlt(offScreenDC, _relativeX - width, yPos, width, height, 0, 0, width, height);
}
