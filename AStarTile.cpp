#include "AStarTile.h"

HRESULT AStarTile::Init()
{
	color = RGB(210, 100, 50);
	brush = CreateSolidBrush(color);
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	return S_OK;
}

HRESULT AStarTile::Init(int _idx, int _idy)
{
	/*color = RGB(250, 100, 50);
	brush = CreateSolidBrush(color);
	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));*/

	idX = _idx;
	idY = _idy;

	/*pos.x = idX * ASTAR_TILE_WIDTH + ASTAR_TILE_WIDTH / 2;
	pos.y = idY * ASTAR_TILE_HEIGHT + ASTAR_TILE_HEIGHT / 2;

	rc = GetRectToCenter(pos.x, pos.y, ASTAR_TILE_WIDTH, ASTAR_TILE_HEIGHT);*/
	hasEnemy = false;
	return S_OK;
}

void AStarTile::Release()
{
	DeleteObject(brush);
	DeleteObject(pen);
}

void AStarTile::Update()
{
}

void AStarTile::Render(HDC hdc)
{
	SelectObject(hdc, brush);
	FillRect(hdc, &rc, brush);

	SelectObject(hdc, pen);
	RenderRect(hdc, pos.x - (ASTAR_TILE_WIDTH / 2), pos.y - (ASTAR_TILE_HEIGHT / 2), ASTAR_TILE_WIDTH);
}

AStarTile::AStarTile()
{
}


AStarTile::~AStarTile()
{
}
