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
	// 몬스터가 있는가? -> 몬스터가 있다가도 죽으면 false 처리 
	bool hasEnemy;
	// 몬스터가 활성화 되었는가?-> 활성화 조건은 특정 인덱스 
	bool actEnemy;
	//획득할 아이템이 있는가?
	bool hasItem;
	// 링크가 범위내에 있는가?
	bool isLinkArea; //해당 경우 몬스터가 있는 타일만 해당 
	// 몬스터가 공격을 당했는가?
	bool hasHitting;// 몬스터가 활성화 되어 있을때만 가능
	// 몬스터가 죽었는가?
	// 출력될 몬스터의 타입 또는 넘버( 몬스터의 넘버는 조금더 생각해 보기 )
	int enemyId;
	//몬스터 출력 위치 
	int tilePosX, tilePosY;

	bool hitLoop;
	//A*관련 변수 

	bool isOneTile;

	bool isMove;

	// 현재 필드의 인덱스 번호 ( FieldInfo 의 인덱스가 아니라   tilePosX, tilePosY;)
	POINT currPos; //
	//현재 클릭된 인덱스 번호 
	//POINT clickPos;
	// 현재 링크의 인덱스 번호 
	POINT linkIndexPos;
	POINT fixlinkIndexPos;
	// 계산된 포스
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

