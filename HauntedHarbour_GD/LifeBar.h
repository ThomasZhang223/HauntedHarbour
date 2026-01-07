#pragma once

#include "GraphicsObject.h"
#include "PlayerObject.h"


class LifeBar
{
public:
	PlayerObject* playerRef;

	LifeBar(PlayerObject* pRef);
	~LifeBar();

	void Draw(HDC screen);
};

