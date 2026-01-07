#include "GraphicsObject.h"


GraphicsObject::GraphicsObject(CString fileName, int xPos, int yPos, int w, int h)
{
	ID = fileName;
	width = w;
	height = h;
	hitWidth = width;
	hitHeight = height;
	this->xPos = xPos;
	this->yPos = yPos;
	picX = 0;
	picY = 0;
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bIsLooping = true;

	image.Load(ID);
}

GraphicsObject::~GraphicsObject()
{

}

void GraphicsObject::Draw(HDC offScreenDC)
{
	// Set the pink color to be used as a transparency channel
	image.SetTransparentColor(RGB(255, 174, 201));

	// Draw on the screen
	image.TransparentBlt(
		offScreenDC,		// Destination DC
		xPos - mapPosition,	// x position of the Destination DC
		yPos,					// y position of the Destination DC
		width,				// width of the Destination DC
		height,				// height of the Destination DC
		picX,				// x position of the Source DC
		picY,				// y position of the Source DC
		width,				// width of the Source DC
		height				// height of the Source DC
	);
}

void GraphicsObject::Animate()
{
	// Update the current cell
	currentCell++;

	if (currentCell >= endCell)
	{
		if (bIsLooping == true)
		{
			currentCell = startCell;
		}
		else
		{
			currentCell = endCell;
		}
	}

	// Update the drawing position
	picX = width * currentCell;
}

bool GraphicsObject::IsColliding(GraphicsObject* entity)
{
	// check left and right of the entity to collide to
	if ((this->xPos + hitWidth > entity->xPos) && (this->xPos < entity->xPos + entity->hitWidth))
	{
		// check top and bottom of the entity to collide to
		if ((this->yPos + hitHeight > entity->yPos) && (this->yPos < entity->yPos + entity->hitHeight))
		{
			return true;
		}
	}

	return false;
}
