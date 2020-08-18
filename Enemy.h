#pragma once
#include "GameNode.h"
#include <list>
#include <vector>

class Image;
class Missile;
class MissileManager;
class Animation;
class Link;
class FieldMapScene;
class AStarTile;
class Enemy : public GameNode
{
protected:
	int indexNum;
	int typeNum;
	POINT posIndex;
	Image* moveImg;
	Image* attImg;
	Animation* moveAni;
	Animation* attAni;
	Animation* playAni;
	Link* link;
	int currFrameX, currFrameY;
	TILE_INFO* tileInfo;
	TILE_INFO* fieldTileInfo;
	FPOINT currTilePos;
	int tiletX;
	int tiletY;
	int tiletX1;
	int  tiletY1;
	MOVE enemystate;
	list<POINT> pathList;
	int hitcount;
	int tempHitcount;

	bool isDie;
	bool isAttMode;
	// ���Ͱ� �ִ°�? -> ���Ͱ� �ִٰ��� ������ false ó�� 
	bool hasEnemy;
	// ���Ͱ� Ȱ��ȭ �Ǿ��°�?-> Ȱ��ȭ ������ Ư�� �ε��� 
	bool actEnemy;
	//ȹ���� �������� �ִ°�?
	bool hasItem;
	// ��ũ�� �������� �ִ°�?
	bool isLinkArea; //�ش� ��� ���Ͱ� �ִ� Ÿ�ϸ� �ش� 
	// ���Ͱ� ������ ���ߴ°�?
	bool hasHitting;// ���Ͱ� Ȱ��ȭ �Ǿ� �������� ����
	// ���Ͱ� �׾��°�?
	// ��µ� ������ Ÿ�� �Ǵ� �ѹ�( ������ �ѹ��� ���ݴ� ������ ���� )
	int enemyId;
	//���� ��� ��ġ 
	int tilePosX, tilePosY;

	bool hitLoop;
	//A*���� ���� 

	bool isOneTile;

	bool isMove;

	// ���� �ʵ��� �ε��� ��ȣ ( FieldInfo �� �ε����� �ƴ϶�   tilePosX, tilePosY;)
	POINT currPos; //
	//���� Ŭ���� �ε��� ��ȣ 
	//POINT clickPos;
	// ���� ��ũ�� �ε��� ��ȣ 
	POINT linkIndexPos;
	POINT fixlinkIndexPos;
	// ���� ����
	POINT resultPos;
	vector<AStarTile*> tiles;
	POINT tempPos;

	float minH;
	AStarTile* lastMinTile;
	AStarTile*	startTile;
	AStarTile*	endTile;
	AStarTile*	currTile;
	int openListSize;
	vector<AStarTile*> openList;
	vector<AStarTile*> closeList;
	bool AttSetting;
	bool hasPath;
	float FindPathTime;
	float moveTime;
	float attTime;
	bool iswaitTime;
	bool isFirstAtt;
	float hitTime;
	FPOINT movePos;

public:
	virtual HRESULT Init();
	//virtual HRESULT Init(int posIndexX, int posIndexY);
	HRESULT Init(int _indexNum);//, int enemyNum = 0);
	//HRESULT Init(int posIndexX, int posIndexY, int enemyNum = 0);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Load();
	void MovePath(int x, int y);
	void AstarPath(AStarTile* currentTile);
	void AddOpenList(AStarTile * currentTile);
	void MovePathCheck();
	void SetTypeNum(int _typeNum) { typeNum = _typeNum; }
	int GetTypeNum() { return typeNum; }

	void AttMotion();
	void AttCheck();

	void SetLink(Link* _link) { link = _link; }

	bool GetIsDie() { return isDie; }

	void SetIsDie(bool _isdie) { isDie = _isdie; }
	bool GetIsAttMode() { return isAttMode; }
	void SetIsAttMode(bool _isAttMode) { isAttMode = _isAttMode; }
	bool GetActEnemy() { return actEnemy; }
	void SetActEnemy(bool _actEnemy) { actEnemy = _actEnemy; }
	bool GetHasHitting() { return hasHitting; }
	void SetHasHitting(bool _hasHitting) { hasHitting = _hasHitting; }
	bool GetIsLinkArea() { return isLinkArea; }
	void SetIsLinkArea(bool _isLinkArea) { isLinkArea = _isLinkArea; }
	int GetIndexNum() { return indexNum; }
	void SetMovePos(FPOINT _movePos) { movePos = _movePos; }
	FPOINT GetMovePos() { return movePos; }


	void SetTilePosX(int _tilePosX) { tilePosX = _tilePosX; }
	int GetTilePosX() { return tilePosX; }
	void SetTilePosY(int _tilePosY) { tilePosY = _tilePosY; }
	int GetTilePosY() { return tilePosY; }


	void SetHitCount(int _hitcount) { hitcount = _hitcount; }

	int GetHitCount() { return hitcount; }

	void SetFieldTileInfo(TILE_INFO* _fieldTileInfo) { fieldTileInfo = _fieldTileInfo; }
	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	//void SetTarget(Tank* tank);
	//FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

