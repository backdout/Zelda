#pragma once
#include "GameNode.h"

#define ASTAR_TILE_WIDTH	64
#define ASTAR_TILE_HEIGHT	64
class Enemy;
class AStarTile : public GameNode
{
private:
	int idX, idY;
	RECT rc;
	
	float totalCost; // F = G + H
	float costFromStart; // G : ���������� ���� ������ ��� ���
	float costToGoal;	// H : ���� ������ ������������ ���� ��κ��

	AStarTile* parentTile;
	TERRAIN attribute;;	// �Ӽ� 

	COLORREF	color;
	HBRUSH		brush;
	HPEN		pen;
	bool hasEnemy;
public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init(int _idx, int _idy);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetTotalCost(float cost) { totalCost = cost; }
	void SetCostFromStart(float cost) { costFromStart = cost; }
	void SetCostToGoal(float cost) { costToGoal = cost; }

	void SetParentTile(AStarTile* parent) { parentTile = parent; }
	void SetAttribute(TERRAIN attr) { attribute = attr;}
	void SetHasEnemy(bool _hasEnemy) { hasEnemy = _hasEnemy; }
	bool GetHasEnemy() {return hasEnemy; }
	void SetColor(COLORREF colorRef) 
	{ 
		DeleteObject(brush);
		color = colorRef;
		brush = CreateSolidBrush(color);
	}
	

	int GetIdX() { return idX; }
	int GetIdY() { return idY; }
	RECT GetRect() { return rc; }
	AStarTile* GetParentTile() { return parentTile; }
	TERRAIN GetAttribute() { return attribute; }
	float GetCostFromStart() { return costFromStart; }

	AStarTile();
	~AStarTile();
};

