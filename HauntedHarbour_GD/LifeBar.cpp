#include "LifeBar.h"


LifeBar::LifeBar(PlayerObject* pRef)
{
	this->playerRef = pRef;
}

LifeBar::~LifeBar(){}

void LifeBar::Draw(HDC screen)
{
	int _remainingHealth = 80 * (double)playerRef->currentHealth / playerRef->maxHealth;

	// Define red and white brushes
	HBRUSH _hbrRed, _hbrWhite;

	// Define colors represented by brushes
	_hbrRed = CreateSolidBrush(RGB(255, 0, 0));
	_hbrWhite = CreateSolidBrush(RGB(255, 255, 255));

	// Tell the screen to use the red brush
	SelectObject(screen, _hbrRed);
	Rectangle(screen, 10, 10, 90, 20);

	// Tell the screen to use the white brush
	SelectObject(screen, _hbrWhite);
	Rectangle(screen, 10 + _remainingHealth, 10, 90, 20);

	// Delete the brushes from memory
	DeleteObject(_hbrRed);
	DeleteObject(_hbrWhite);
}
