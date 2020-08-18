#pragma once

#include "GameNode.h"
#include "pch.h"
#include <algorithm>
#include <deque>


class Button;
class ButtonFunc;
class Missile;
class Enemy;
class EnemyManager;
class LoadingScene;
class Link;
class Castlemap : public GameNode
{
private:


	Image* bg;
	Image* king;
	Image* bord;
	Image* bord2;
	Image* cuser;
	HFONT font, oldfont;
	char szText[128];
	HPEN hPen, hOldPen;
	Image* sampleTileImage;
	TILE_INFO CastleTileInfo[SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y];
	TILE_INFO PosTile[(TILE_Y + 1)*(TILE_X + 4)];
	Link * link;
	FPOINT linkPos;
	int enemyCount;
	int enemyDieCount;

	float scale;
	float enemyShowTime;
	float enemyShowTimeCount;
	int mouseIndex;
	int rotationX, rotationY;
	int printIndex;
	POINT clickPos;
	POINT movePoint;
	deque<POINT> pathList;
	POINT cuserFrame;
	float moveTime;
	float scriptTime;
	int tilePosX, tilePosY;
	//string tutoScript[];
	vector<string> tutoScript;
	vector<string> questScript1;
	vector<string> questScript2;
	vector<string> questScript3;
	vector<string> ending;
	bool isQuestPrint;
	string printScript;
	int scriptNum;
	RECT scriptZone;
	bool hasTutorial1;
	string questClearNum;
	bool isEnding;


public:
		virtual HRESULT Init();
		virtual void Release();		// 메모리 해제
		virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
		virtual void Render(HDC hdc);


		void Load();
		void Save();
		void PrintRect();
		POINT GetClickPos() { return clickPos; }
		void MapRender(HDC hdc);
		
		void LinkAtt();
		void MoveClickCheck();

		void ScriptSetting(string fileName);
	
		void QuestClickCheck();
		void Tutorial();
		void Quest1();
		void Quest2();
		
		void Quest3();
		void Ending();

		void QuestStatus(HDC hdc);


		Castlemap();
		virtual ~Castlemap();

};

