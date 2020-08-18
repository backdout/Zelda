#pragma once
#include "GameNode.h"
#include "pch.h"

//640*288  20*9(32*32)

enum TANKTERRAIN
{
	//TTR_GRASS,
	TTR_OBJ = -1,
	TTR_NONE = 0,
	TTR_R_REDBLOCK,//1
	TTR_L_REDBLOCK,//2
	TTR_U_REDBLOCK,//3
	TTR_D_REDBLOCK,//4
	TTR_REDBLOCK,//5 //1
	TTR_R_IRON,//6
	TTR_L_IRON,//7
	TTR_U_IRON,//8
	TTR_D_IRON,//9
	TTR_IRON,//10//2
	TTR_WEED,//11//3
	TTR_WATER,//12//4
	TTR_ENEMY,//13//5
	TTR_KING,//14//6
	TTR_S_L_REDBLOCK,//15//7
	TTR_S_R_REDBLOCK,//16//8
	TTR_END // 이넘의 갯수을 알기위한 변수
};


typedef struct tagSelectTile
{

	//RECT rcTile;
	int frameX;
	int frameY;
	TERRAIN  terrain;

}SELECT_TILE_INFO;

typedef struct tagTank
{

	RECT rcTile;
	int frameX;
	int frameY;
	int posX;
	int posY;
	bool isSelect;
	TERRAIN  terrain;
	TANKTERRAIN  tankTerrain;
}Tank_INFO;


class Button;
class ButtonFunc;
class Image;
class Construction :public GameNode
{
private:
	Image* sampleTileImage;
	Image* sampleTileImage2;
	Image* sampleTileImage3;
	Image* objTileImage;
	Image* tankImg;
	Image* bgImg;
	Image* mapBg;
	Image* cursor;
	Image* mapBord;
	Image* sampleBord;
	Image* buttonBord;

	ButtonFunc* buttonFunc;

	Button*		saveButton;
	Button*		loadButton;
	Button*		mapOrObjButton;
	
	Button*		sampleLeftBt;
	Button*		sampleRightBt;
	Button*		sampleUpBt;
	Button*		sampleDownBt;
	Button*		leftBt;
	Button*		rightBt;
	Button*		upBt;
	Button*		downBt;
	Button*		fieldBt;
	Button*		castleBt;
	Button*		dungeonBt;
	Button*		terrainBt;

	Button*		noneBt;
	Button*		blockBt;
	Button*		waterBt;
	Button*		cliffBt;
	Button*		objBt;

	POINT cuserFrame;
	//Button* objBt;
	
	int indexNum;
	int sampleindexNum;
	int printIndex;
	int fieldTile = (SAMPLEFIELDTILE_Y_1 + SAMPLEFIELDTILE_Y_2) *SAMPLEFIELDTILE_X_2;
	// 샘플 타일의 정보-> 시작프레임 포인트와  선택하기 위한 렉트 정보  ( 구조체 배열로 저장)
	SMAPLE_TILE_INFO sampleFieldTileInfo[SAMPLEFIELDTILE_X_2* (SAMPLEFIELDTILE_Y_2+ SAMPLEFIELDTILE_Y_1)];
	SMAPLE_TILE_INFO sampleCastleTileInfo[SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y];
	SMAPLE_TILE_INFO sampleDungeonTileInfo[SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y];
	SMAPLE_TILE_INFO sampleTileInfo[SAMPLETILE_X* SAMPLETILE_Y];

	//Dungeon
	//objectTile
	SMAPLE_TILE_INFO objTileInfo[OBJTILE_X* OBJTILE_Y];

	//메인 타일의 정보 -> 렉트 정보 / 샘플 타일의 시작 프레임 포인트 /타일의 속성
	TILE_INFO tileInfo[(TILE_X* TILE_Y)];
	//TILE_INFO tileInfo[(156 * 62) + (122 * 63)];
	//TILE_INFO FieldTileInfo[(SAMPLEFIELDTILE_X_1* SAMPLEFIELDTILE_Y_1) + (SAMPLEFIELDTILE_X_2* SAMPLEFIELDTILE_Y_2)];
	
	TILE_INFO FieldTileInfo[FIELDTILE_X_2* (FIELDTILE_Y_2 + FIELDTILE_Y_1)];
	TILE_MONS_INFO FieldTileMonsInfo[FIELDTILE_X_2* (FIELDTILE_Y_2 + FIELDTILE_Y_1)];
	TILE_INFO CastleTileInfo[SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y];
	TILE_INFO DungeonTileInfo[SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y];
	TILE_INFO TileInfo[SAMPLETILE_X* SAMPLETILE_Y];

	
	//TILE_INFO tempInfo''
	// 선택된 타일의 정보 (샘플 타일에서 ) -> 시작 프레임 정보 
	Tank_INFO tank;
	SELECT_TILE_INFO selectTileInfo;
	SELECT_TILE_INFO selectTileInfos[2];
	RECT totalTileSize;
	//세이브 로드

	float scale;
	bool isDownSample;
	int minX, minY, maxX, maxY;
	int dragSizeX ;
	int dragSizeY ;

	int tilePosX, tilePosY;
	int sampletilePosX, sampletilePosY;

	bool isFieldSelect;
	bool isCastleSelect;
	bool isDungeonSelect;
	bool isTerraninSelect;
	bool isNoneSelect;
	bool isBlockSelect;
	bool isWaterSelect;
	bool isCliffSelect;
	bool isObjSelect;



public:
	virtual HRESULT Init() override;
	virtual void Release()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;



	void ButtonUpdate();

	void Save();
	void Load();
	void Reset();

	void DrawSampleFieldRect();
	void DrawFieldRect();
	void PrintFieldRect();
	void RenderFieldTile(HDC hdc);
	void AttachFieldTile();





	void DrawSampleCastleRect();
	void DrawCastleRect();
	void PrintCastleRect();
	void RenderCastleTile(HDC hdc);
	void AttachCastleTile();


	void DrawSampleDungeonRect();
	void DrawDungeonRect();
	void PrintDungeonRect();
	void RenderDungeonTile(HDC hdc);
	void AttachDungeonTile();






	void ChangeTerrain(TANKTERRAIN  tankTerrain);

	Construction();
	~Construction();
};


