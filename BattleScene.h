#pragma once
#include "GameNode.h"
#include "pch.h"


class Missile;
class Enemy;
class EnemyManager;
class LoadingScene;
class Link;
class BattleScene : public GameNode
{
private:
	
	Image* bg;
	Image* gameOver;

	Image* clear;

	LoadingScene* load;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	Image* sampleTileImage;
	TILE_INFO tileInfo[TILE_X* TILE_Y];
	//Enemy* enemy;
	float scale;
	RECT totalTileSize;
	EnemyManager* enemyMgr;
	Link * Tank1p;
	RECT tankRect;
	float enemyShowTime;
	float enemyShowTimeCount;
	int enemyCount;
	int enemyDieCount;
	bool isGameOver;
	bool isGameClear;
	int stageNum;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(bool goToCons); // ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	 void SetLoadingScene(LoadingScene* _load) { load = _load; }
	 void Load();
	 void stageLoad(int num);
	 void Save();


	BattleScene();
	virtual ~BattleScene();
};

