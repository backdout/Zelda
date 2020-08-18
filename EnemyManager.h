#pragma once
#include "GameNode.h"
#include <fstream>


#include <vector>
#include <map>

typedef struct EnemyInfo
{

	int type;
	int index;
	bool isDie;
}ENEMY_INFO;





class Image;
class Enemy;
class Link;
class EnemyManager : public GameNode
{
private:
	int vecIndeX;
	map<int, Enemy*> enemy1;
	map<int, Enemy*> saveEnemy;
	map<int, Enemy*> loadEnemy;
	POINT posIndex;

	vector<Enemy*>	vecEnemys;
	vector<Enemy*>::iterator	itEnemys;

	vector<int> enemy1IndexPos;

	TILE_INFO* tileInfo;
	TILE_INFO* fieldTileInfo;
	ENEMY_INFO enemyInfo[50];

	bool isLoad;
	Link* link;
	bool isSetting;
	Image* addImg;
	int dieCount;
	int tilePosX, tilePosY;
	FPOINT movePos;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetLink(Link* _link) { link = _link; }
	void SetEnemy1IndexPos();
	int GetDieCount() { return dieCount; }
	void AddEnemy(float posX, float posY);
	void SetTileInfo(TILE_INFO* _tileInfo) { tileInfo = _tileInfo; }
	void SetFieldTileInfo(TILE_INFO* _fieldTileInfo) { fieldTileInfo = _fieldTileInfo; }
	void SetMovePos(FPOINT _movePos) { movePos = _movePos; }
	FPOINT GetMovePos() { return movePos; }


	void SetTilePosX(int _tilePosX) { tilePosX = _tilePosX; }
	int GetTilePosX() { return tilePosX; }
	void SetTilePosY(int _tilePosY) { tilePosY = _tilePosY; }
	int GetTilePosY() { return tilePosY; }
	vector<int> GetEnemy1IndexPos() { return enemy1IndexPos; }
	void SetisLoad(bool _isLoad) { isLoad = _isLoad; }


	void Save();
	void Load();




	EnemyManager();
	~EnemyManager();
};

