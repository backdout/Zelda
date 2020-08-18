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
	float costFromStart; // G : 시작점부터 현재 노드까지 경로 비용
	float costToGoal;	// H : 현재 노드부터 도착노드까지의 예상 경로비용

	AStarTile* parentTile;
	TERRAIN attribute;;	// 속성 

	COLORREF	color;
	HBRUSH		brush;
	HPEN		pen;
	bool hasEnemy;
public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	HRESULT Init(int _idx, int _idy);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

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

