#include "Construction.h"
#include "Image.h"
#include "macroFunction.h"
#include "Button.h"
#include "ButtonFunc.h"

HRESULT Construction::Init()
{
	
	minX = 0;
	maxX = 0;
	minY = 0;
	maxY = 0;
	dragSizeX = 0;
	dragSizeY = 0;
	scale = 2.0f;


	isFieldSelect = true;
	isCastleSelect = false;
	isDungeonSelect = false;
	isTerraninSelect = false;


	//이미지
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);
	//sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일1", "Image/Field1.bmp", 0, 0, 1008, 1952, SAMPLEFIELDTILE_X_1, SAMPLEFIELDTILE_Y_1);
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일1", "Image/bg1.bmp", 0, 0, 2496, 2944, SAMPLEFIELDTILE_X_2, SAMPLEFIELDTILE_Y_1 + SAMPLEFIELDTILE_Y_2);
	sampleTileImage2 = ImageManager::GetSingleton()->AddImage("샘플타일2", "Image/castlemap.bmp", 0, 0, 624, 240, SAMPLECASTLETILE_X, SAMPLECASTLETILE_Y);
	sampleTileImage3 = ImageManager::GetSingleton()->AddImage("샘플타일3", "Image/던전맵.bmp", 0, 0, 352, 240, SAMPLEDUNGEONTILE_X, SAMPLEDUNGEONTILE_Y, false , RGB(255,0,255));
	bgImg = ImageManager::GetSingleton()->AddImage("MapBG", "Image/mapbg.bmp", 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y, 1, 1);
	cursor = ImageManager::GetSingleton()->AddImage("커서", "Image/커서.bmp", 0, 0, 150, 225, 2, 3, true, RGB(68, 75, 79));
	mapBord = ImageManager::GetSingleton()->AddImage("bord", "Image/bord.bmp", 0, 0, 493, 498, 1, 1, true, RGB(167, 167, 227));
	sampleBord = ImageManager::GetSingleton()->AddImage("bord1", "Image/bord.bmp", 0, 0, 493, 498, 1, 1, true, RGB(167, 167, 227));

	buttonBord = ImageManager::GetSingleton()->AddImage("bord2", "Image/btbord.bmp", 0, 0, 1050, 300, 1, 1, true, RGB(167, 167, 227));


	ImageManager::GetSingleton()->AddImage("화살표", "Image/화살표.bmp", 0.0f, 0.0f, 80, 40, 4, 2);
	ImageManager::GetSingleton()->AddImage("맵버튼", "Image/맵타입버튼.bmp", 0.0f, 0.0f, 152,124, 2, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("터레인버튼", "Image/터레인버튼.bmp", 0.0f, 0.0f, 300,40, 5, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("세이브", "Image/saveUi.bmp", 0.0f, 0.0f, 300, 46, 4, 2, true, RGB(167, 167, 227));

	// 버튼
	buttonFunc = new ButtonFunc();
	buttonFunc->Init();
	 POINT upFramePoint = { 0, 0 };
	 POINT downFramePoint = { 0, 1 };
	// 화살표 버튼 
	 sampleLeftBt = new Button;
	 sampleLeftBt-> Init("화살표", 740, 530,  downFramePoint, upFramePoint);
	 sampleLeftBt->SetButtonFunc(buttonFunc, &ButtonFunc::SampleMapLeft);
	 sampleLeftBt->SetIsDirBt(true);

	 leftBt = new Button;
	 leftBt->Init("화살표", 140, 530, downFramePoint, upFramePoint);
	 leftBt->SetButtonFunc(buttonFunc, &ButtonFunc::MapLeft);
	 leftBt->SetIsDirBt(true);

	 upFramePoint = { 1, 0 };
	 downFramePoint = { 1, 1 };
	 sampleRightBt = new Button;
	 sampleRightBt->Init("화살표", 840, 530, downFramePoint, upFramePoint);
	 sampleRightBt->SetButtonFunc(buttonFunc, &ButtonFunc::SampleMapRight);
	 sampleRightBt->SetIsDirBt(true);

	 rightBt = new Button;
	 rightBt->Init("화살표", 240, 530, downFramePoint, upFramePoint);
	 rightBt->SetButtonFunc(buttonFunc, &ButtonFunc::MapRight);
	 rightBt->SetIsDirBt(true);

	 upFramePoint = { 2, 0 };
	 downFramePoint = { 2, 1 };
	 sampleUpBt = new Button;
	 sampleUpBt->Init("화살표", 1060, 240, downFramePoint, upFramePoint);
	 sampleUpBt->SetButtonFunc(buttonFunc, &ButtonFunc::SampleMapUp);
	 sampleUpBt->SetIsDirBt(true);

	 upBt = new Button;
	 upBt->Init("화살표", 520, 240, downFramePoint, upFramePoint);
	 upBt->SetButtonFunc(buttonFunc, &ButtonFunc::MapUp);
	 upBt->SetIsDirBt(true);

	 upFramePoint = { 3, 0 };
	 downFramePoint = {3, 1 };
	 sampleDownBt = new Button;
	 sampleDownBt->Init("화살표", 1060, 340,  downFramePoint, upFramePoint);
	 sampleDownBt->SetButtonFunc(buttonFunc, &ButtonFunc::SampleMapDown);
	 sampleDownBt->SetIsDirBt(true);

	 downBt = new Button;
	 downBt->Init("화살표", 520, 340, downFramePoint, upFramePoint);
	 downBt->SetButtonFunc(buttonFunc, &ButtonFunc::MapDown);
	 downBt->SetIsDirBt(true);

	 upFramePoint = { 0, 0 };
	 downFramePoint = { 1, 0 };
	 fieldBt = new Button;
	 fieldBt->Init("맵버튼", 130, 640, downFramePoint, upFramePoint);
	 fieldBt->SetButtonFunc(buttonFunc, &ButtonFunc::FieldBt);

	 upFramePoint = { 0, 1 };
	 downFramePoint = { 1, 1 };
	 castleBt = new Button;
	 castleBt->Init("맵버튼", 130, 720, downFramePoint, upFramePoint);
	 castleBt->SetButtonFunc(buttonFunc, &ButtonFunc::CastleBt);

	 upFramePoint = { 0, 2 };
	 downFramePoint = { 1, 2 };
	 dungeonBt = new Button;
	 dungeonBt->Init("맵버튼", 130, 800, downFramePoint, upFramePoint);
	 dungeonBt->SetButtonFunc(buttonFunc, &ButtonFunc::DungeonBt);


	 upFramePoint = { 0, 3 };
	 downFramePoint = { 1, 3 };
	 terrainBt = new Button;
	 terrainBt->Init("맵버튼", 350, 640, downFramePoint, upFramePoint);
	 terrainBt->SetButtonFunc(buttonFunc, &ButtonFunc::TerrainBt);


	 upFramePoint = { 0, 0 };
	 downFramePoint = { 0, 1 };
	noneBt = new Button;
	noneBt->Init("터레인버튼", 10, 4, downFramePoint, upFramePoint);
	noneBt->SetButtonFunc(buttonFunc, &ButtonFunc::NoneBt);
	
	upFramePoint = { 1, 0 };
	downFramePoint = { 1, 1 };
	blockBt = new Button;
	blockBt->Init("터레인버튼", 160, 4, downFramePoint, upFramePoint);
	blockBt->SetButtonFunc(buttonFunc, &ButtonFunc::BlockBt);
	
	upFramePoint = { 2, 0 };
	downFramePoint = { 2, 1 };
	waterBt = new Button;
	waterBt->Init("터레인버튼", 310, 4, downFramePoint, upFramePoint);
	waterBt->SetButtonFunc(buttonFunc, &ButtonFunc::WaterBt);
	
	upFramePoint = { 3, 0 };
	downFramePoint = { 3, 1 };
	cliffBt = new Button;
	cliffBt->Init("터레인버튼", 460, 4, downFramePoint, upFramePoint);
	cliffBt->SetButtonFunc(buttonFunc, &ButtonFunc::CliffBt);
	
	upFramePoint = { 4, 0 };
	downFramePoint = { 4, 1 };
	objBt = new Button;
	objBt->Init("터레인버튼", 610, 4, downFramePoint, upFramePoint);
	objBt->SetButtonFunc(buttonFunc, &ButtonFunc::ObjBt);




	 for (int i = 0; i < (SAMPLEFIELDTILE_Y_1 + SAMPLEFIELDTILE_Y_2); i++)
	 {
		 for (int j = 0; j < SAMPLEFIELDTILE_X_2; j++)
		 {
			 sampleFieldTileInfo[i*SAMPLEFIELDTILE_X_2 + j].frameX = j;
			 sampleFieldTileInfo[i*SAMPLEFIELDTILE_X_2 + j].frameY = i;
		 }	
	 }

	 for (int i = 0; i < SAMPLECASTLETILE_Y; i++)
	 {
		 for (int j = 0; j < SAMPLECASTLETILE_X; j++)
		 {
			 sampleCastleTileInfo[i*SAMPLECASTLETILE_X + j].frameX = j;
			 sampleCastleTileInfo[i*SAMPLECASTLETILE_X + j].frameY = i;
		 }
	 }


	 for (int i = 0; i < SAMPLEDUNGEONTILE_Y; i++)
	 {
		 for (int j = 0; j < SAMPLEDUNGEONTILE_X; j++)
		 {
			 sampleDungeonTileInfo[i*SAMPLEDUNGEONTILE_X + j].frameX = j;
			 sampleDungeonTileInfo[i*SAMPLEDUNGEONTILE_X + j].frameY = i;
		 }
	 }




	 for (int i = 0; i < (FIELDTILE_Y_1 + FIELDTILE_Y_2); i++)	
	 {
		 for (int j = 0; j < FIELDTILE_X_2; j++)
		 {
			 FieldTileInfo[i*FIELDTILE_X_2 + j].frameX = j;
			 FieldTileInfo[i*FIELDTILE_X_2 + j].frameY = i;
		 }
	 }

	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;

	selectTileInfos[0].frameX = 0;
	selectTileInfos[0].frameY = 0;
	selectTileInfos[1].frameX = 0;
	selectTileInfos[1].frameY = 0;

	// 왼쪽에 그려질 내용을 초기화 한다. ( 기본-> 잔디로 설정)
	tank.posX = 0;
	tank.posY = 0;
	tank.isSelect = true;

	tilePosX = 0;
	tilePosY = 0;
	//DrawFieldRect();
	//Load();
	//SetCursor(true);
	ShowCursor(true);
	return S_OK;
}

void Construction::Release()
{

}

void Construction::Update()
{


	ButtonUpdate();

	if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
	{
		Save();
		//SceneManager::GetSingleton()->ChangeScene("타이틀");
		return;	//체인지되며 밑에있는 애들 랜더 안시키기위해
	}


	if (KeyManager::GetSingleton()->IsOnceKeyUp('R'))
	{
		Load();
	}



	
		
		if (isFieldSelect)
		{

			for (int i = 0; i < fieldTile; i++)
			{
				if (PtInRect(&FieldTileInfo[i].rcTile, g_ptMouse))
				{
					indexNum = i;
				}
				if (PtInRect(&sampleFieldTileInfo[i].rcTile, g_ptMouse))
				{
					sampleindexNum = i;
				}
			}
			PrintFieldRect();
			DrawSampleFieldRect();
			AttachFieldTile();
		}
		if (isCastleSelect)
		{

			for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
			{
				if (PtInRect(&CastleTileInfo[i].rcTile, g_ptMouse))
				{
					indexNum = i;
				}
				if (PtInRect(&sampleCastleTileInfo[i].rcTile, g_ptMouse))
				{
					sampleindexNum = i;
				}
			}
			PrintCastleRect();
			DrawSampleCastleRect();
			AttachCastleTile();
		}


		if (isDungeonSelect)
		{

			for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
			{
				if (PtInRect(&DungeonTileInfo[i].rcTile, g_ptMouse))
				{
					indexNum = i;
				}
				if (PtInRect(&sampleDungeonTileInfo[i].rcTile, g_ptMouse))
				{
					sampleindexNum = i;
				}
			}
			PrintDungeonRect();
			DrawSampleDungeonRect();
			AttachDungeonTile();
		}


			
}

void Construction::Render(HDC hdc)
{

	//PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_Y, BLACKNESS);
	bgImg->Render(hdc, 0, 0);

	buttonBord->Render(hdc, 20, 590);
	
	if (isFieldSelect) RenderFieldTile(hdc);
	if (isCastleSelect) RenderCastleTile(hdc);
	if (isDungeonSelect)RenderDungeonTile(hdc);
	
	if (sampleLeftBt)sampleLeftBt->Render(hdc);
	if (sampleRightBt)sampleRightBt->Render(hdc);
	if (sampleUpBt)sampleUpBt->Render(hdc);
	if (sampleDownBt)sampleDownBt->Render(hdc);
	if (leftBt)leftBt->Render(hdc);
	if (rightBt)rightBt->Render(hdc);
	if (upBt)upBt->Render(hdc);
	if (downBt)downBt->Render(hdc);
	if (fieldBt)fieldBt->Render(hdc);
	if (dungeonBt)dungeonBt->Render(hdc);
	if (castleBt)castleBt->Render(hdc);
	if (terrainBt)terrainBt->Render(hdc);
	if (castleBt)castleBt->Render(hdc); mapBord->Render(hdc, 20, 20);
	if (terrainBt)terrainBt->Render(hdc); sampleBord->Render(hdc, 560, 20);

	if (isTerraninSelect)
	{
		if (noneBt)noneBt->Render(hdc);
		if (blockBt)blockBt->Render(hdc);
		if (waterBt)waterBt->Render(hdc);
		if (cliffBt)cliffBt->Render(hdc);
		if (objBt)objBt->Render(hdc);
	}
	char szText[128];
	sprintf_s(szText, "현재 마우스 위치 : [ %d , %d , index : %d, sampleindex : %d ]", g_ptMouse.x, g_ptMouse.y,indexNum, sampleindexNum);
	TextOut(hdc, WINSIZE_X - 500, 580, szText, strlen(szText));
	if (isTerraninSelect)
	{
		HFONT font, oldfont;
		font = CreateFont(18, 0, 0, 0, 500, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, "궁서");
		SetTextColor(hdc, RGB(255, 0, 255));
		oldfont = (HFONT)SelectObject(hdc, font);
		sprintf_s(szText, "Terrain Mode On");
		TextOut(hdc, 32, 34, szText, strlen(szText)); //TextOut(hdc, 37, 682, szText, strlen(szText));
		SelectObject(hdc, oldfont);
		DeleteObject(font);
		SetTextColor(hdc, RGB(0, 0, 0));
	}

	
	cursor->FrameRender(hdc, g_ptMouse.x + (cursor->GetFrameWidth() / 2), g_ptMouse.y + (cursor->GetFrameHeight() / 2), cuserFrame.x, 0);//Render(hdc, g_ptMouse.x, g_ptMouse.y);

	
}

void Construction::ButtonUpdate()
{
	sampleLeftBt->Update();
	sampleRightBt->Update();
	sampleUpBt->Update();
	sampleDownBt->Update();
	leftBt->Update();
	rightBt->Update();
	upBt->Update();
	downBt->Update();
	fieldBt->Update();
	castleBt->Update();
	dungeonBt->Update();
	terrainBt->Update();
	if (isTerraninSelect)
	{
		noneBt->Update();
		blockBt->Update();
		waterBt->Update();
		cliffBt->Update();
		objBt->Update();
	}
	sampletilePosX = buttonFunc->GetSampletileframeX();
	sampletilePosY = buttonFunc->GetSampletileframeY();

	tilePosX = buttonFunc->GetTileframeX();
	tilePosY = buttonFunc->GetTileframeY();
	
	isFieldSelect = buttonFunc->GetIsFieldSelect();
	isCastleSelect = buttonFunc->GetIsCastleSelect();
	isDungeonSelect = buttonFunc->GetIsDungeonSelect();
	isTerraninSelect = buttonFunc->GetIsTerraninSelect();
	if (isTerraninSelect)
	{
		isNoneSelect = buttonFunc->GetIisNoneSelect();
		isBlockSelect = buttonFunc->GetIsBlockSelect();
		isWaterSelect = buttonFunc->GetIsWaterSelect();
		isCliffSelect = buttonFunc->GetIsCliffSelect();
		isObjSelect = buttonFunc->GetIsObjSelect();
	}
}

void Construction::Save()
{
	DrawFieldRect();
	DWORD writtenByte;
	if (isFieldSelect)
	{

		for (int i = 0; i < fieldTile; i++)
		{
			FieldTileMonsInfo[i].frameX = FieldTileInfo[i].frameX;
			FieldTileMonsInfo[i].frameY = FieldTileInfo[i].frameY;
			FieldTileMonsInfo[i].objFrameX = FieldTileInfo[i].objFrameX;
			FieldTileMonsInfo[i].objFrameY = FieldTileInfo[i].objFrameY;
			FieldTileMonsInfo[i].rcTile = FieldTileInfo[i].rcTile;
			FieldTileMonsInfo[i].terrain = FieldTileInfo[i].terrain;


		}


		/*HANDLE hFile = CreateFile("Save/Field", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, FieldTileInfo, sizeof(TILE_INFO)*fieldTile, &writtenByte, NULL);
		CloseHandle(hFile);*/
		HANDLE hFile = CreateFile("Save/SaveField", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, FieldTileMonsInfo, sizeof(TILE_INFO)*fieldTile, &writtenByte, NULL);
		CloseHandle(hFile);
	}
	else if (isCastleSelect)
	{
		HANDLE hFile = CreateFile("Save/SaveCastle.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, CastleTileInfo, sizeof(TILE_INFO)*SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);
	}
	else if (isDungeonSelect)
	{
		HANDLE hFile = CreateFile("Save/SaveDungeon.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, DungeonTileInfo, sizeof(TILE_INFO)*SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);
	}
	
}

void Construction::Load()
{
	if (isFieldSelect)
	{
		DWORD readByte;
		HANDLE hFile = CreateFile("Save/Field", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, FieldTileInfo, sizeof(TILE_INFO)*fieldTile, &readByte, NULL);
		CloseHandle(hFile);

		for (int i = 0; i < fieldTile; i++)
		{
			FieldTileMonsInfo[i].frameX = FieldTileInfo[i].frameX;
			FieldTileMonsInfo[i].frameY = FieldTileInfo[i].frameY;
			FieldTileMonsInfo[i].objFrameX = FieldTileInfo[i].objFrameX;
			FieldTileMonsInfo[i].objFrameY = FieldTileInfo[i].objFrameY;
			FieldTileMonsInfo[i].rcTile = FieldTileInfo[i].rcTile;
			FieldTileMonsInfo[i].terrain = FieldTileInfo[i].terrain;


		}
	}
	if (isCastleSelect)
	{
		DWORD readByte;
		HANDLE hFile = CreateFile("Save/Castle.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, CastleTileInfo, sizeof(TILE_INFO)*SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}
	
	if (isDungeonSelect)
	{
		DWORD readByte;
		HANDLE hFile = CreateFile("Save/Dungeon.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, DungeonTileInfo, sizeof(TILE_INFO)*SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}


}

void Construction::Reset()
{

}

void Construction::DrawSampleFieldRect()
{
		
	int Tile = 121 * SAMPLEFIELDTILE_X_2;
	
	if (sampletilePosY < SAMPLEFIELDTILE_Y_1 + SAMPLEFIELDTILE_Y_2 )
	{
		for (int i = 0; i < fieldTile; i++)
		{
			SetRect(&sampleFieldTileInfo[i].rcTile,
				0, 0, 0, 0);
		}
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEFIELDTILE_X_2) + (i* SAMPLEFIELDTILE_X_2) + sampletilePosX + j;
				SetRect(&sampleFieldTileInfo[printIndex].rcTile,
					j * TILESIZE*scale +(WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72, i*TILESIZE*scale + 47, j * TILESIZE*scale+ TILESIZE * scale  + (WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72,
					i*TILESIZE*scale + TILESIZE * scale + 47);
			}
	

		}
	}
	


}

void Construction::DrawFieldRect()
{
	int Tile = 122 * FIELDTILE_X_1;
	for (int i = 0; i < (FIELDTILE_Y_1 + FIELDTILE_Y_2); i++)
	{
		for (int j = 0; j < FIELDTILE_X_2; j++)
		{
			
			SetRect(&FieldTileInfo[i*FIELDTILE_X_2 + j].rcTile,
				j * TILESIZE*scale , i*TILESIZE*scale , j * TILESIZE*scale + TILESIZE * scale,
				i*TILESIZE*scale  + TILESIZE * scale);
		}
		
	}
}

void Construction::PrintFieldRect()
{
//타일
	for (int i = 0; i < fieldTile; i++)
	{
		SetRect(&FieldTileInfo[i].rcTile,
			0, 0, 0, 0);
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < FIELDTILE_X_2 - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * FIELDTILE_X_2) + (i* FIELDTILE_X_2) + tilePosX + j;
				{
					SetRect(&FieldTileInfo[printIndex].rcTile,
						j * (TILESIZE * scale) + 42, i*(TILESIZE*scale) + 47, j * (TILESIZE*scale) + (TILESIZE * scale) + 42,
						i* (TILESIZE*scale) + (TILESIZE * scale) + 47);

				}

			}
		}
		else
		{
			int X = FIELDTILE_X_2 - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * FIELDTILE_X_2) + (i* FIELDTILE_X_2) + tilePosX + j;
				SetRect(&FieldTileInfo[printIndex].rcTile,
					j * TILESIZE*scale + 42, i*TILESIZE*scale + 47, j * TILESIZE*scale + 42 + TILESIZE * scale,
					i*TILESIZE*scale + TILESIZE * scale + 47);

			}
		}

	}
	
}

void Construction::RenderFieldTile(HDC hdc)
{
	//타일렌더 찍는 곳
	HFONT font, oldfont;
	font = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldfont = (HFONT)SelectObject(hdc, font);
	char szText[128];
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < FIELDTILE_X_2 - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * FIELDTILE_X_2) + (i* FIELDTILE_X_2) + tilePosX + j;	
				Rectangle(hdc, FieldTileInfo[printIndex].rcTile.left, FieldTileInfo[printIndex].rcTile.top, FieldTileInfo[printIndex].rcTile.right,FieldTileInfo[printIndex].rcTile.bottom);
				sampleTileImage->FrameRender(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), FieldTileInfo[printIndex].frameX, FieldTileInfo[printIndex].frameY, scale);
				if (FieldTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{
					
					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				
				}
			}
		}
		else
		{
			int X = FIELDTILE_X_2 - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * FIELDTILE_X_2) + (i* FIELDTILE_X_2) + tilePosX + j;
				/*Rectangle(hdc, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.left, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.top, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.right,
					FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.bottom);*/
				sampleTileImage->FrameRender(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), FieldTileInfo[printIndex].frameX, FieldTileInfo[printIndex].frameY, scale);
				if (FieldTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (FieldTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}

			}
		}

	}
	//샘플 렌더
	
	

	for (int i = 0; i < TILE_Y; i++)
	{
		if (sampletilePosX < SAMPLEFIELDTILE_X_2 - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEFIELDTILE_X_2) + (i * SAMPLEFIELDTILE_X_2) + sampletilePosX + j;
				sampleTileImage->FrameRender(hdc, sampleFieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleFieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleFieldTileInfo[printIndex].frameX, sampleFieldTileInfo[printIndex].frameY, scale);
				
				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleFieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleFieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
			
			}
		}
		else
		{
			int X = SAMPLEFIELDTILE_X_2 - sampletilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEFIELDTILE_X_2) + (i * SAMPLEFIELDTILE_X_2) + sampletilePosX + j;
				sampleTileImage->FrameRender(hdc, sampleFieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleFieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleFieldTileInfo[printIndex].frameX, sampleFieldTileInfo[printIndex].frameY, scale);
				
				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleFieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleFieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
			}
		}

	}
	
	SelectObject(hdc, oldfont);
	DeleteObject(font);
	
}

void Construction::AttachFieldTile()
{
	if (!isTerraninSelect)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			cuserFrame.x = 1;
			if (!isDownSample)
			{
				
				for (int i = 0; i < fieldTile; i++)
				{
					if (PtInRect(&sampleFieldTileInfo[i].rcTile, g_ptMouse))
					{
						/*selectTileInfo.frameX = sampleFieldTileInfo[i].frameX;
						selectTileInfo.frameY = sampleFieldTileInfo[i].frameY;*/

						selectTileInfos[0].frameX = sampleFieldTileInfo[i].frameX;
						selectTileInfos[0].frameY = sampleFieldTileInfo[i].frameY;
						isDownSample = true;
						break;// 최대한 돌지 않게;;

					}
				}
			}


		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			cuserFrame.x = 0;
			if (isDownSample)
			{
				for (int i = 0; i < fieldTile; i++)
				{
					if (PtInRect(&sampleFieldTileInfo[i].rcTile, g_ptMouse))
					{
						selectTileInfos[1].frameX = sampleFieldTileInfo[i].frameX;
						selectTileInfos[1].frameY = sampleFieldTileInfo[i].frameY;
						//드래그 영역의 값을 정렬;

						minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
						maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

						dragSizeX = maxX - minX;
						dragSizeY = maxY - minY;
						isDownSample = false;
						break;// 최대한 돌지 않게;;

					}


				}
			}
			else
			{

				for (int i = 0; i < fieldTile; i++)
				{
					if (PtInRect(&FieldTileInfo[i].rcTile, g_ptMouse))
					{
						for (int y = 0; y <= dragSizeY; y++)
						{
							for (int x = 0; x <= dragSizeX; x++)
							{
								if ((i%FIELDTILE_X_2) + x >= FIELDTILE_X_2) continue;
								if ((i / FIELDTILE_X_2) + y >= (FIELDTILE_Y_1 + FIELDTILE_Y_2)) continue;

								FieldTileInfo[i + (y* FIELDTILE_X_2) + x].frameX = minX + x;
								FieldTileInfo[i + (y* FIELDTILE_X_2) + x].frameY = minY + y;
							}
						}
						return;

					}

				}



			}

		}


	}
	else
	{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		cuserFrame.x = 1;
		for (int i = 0; i < fieldTile; i++)
		{
			if (PtInRect(&FieldTileInfo[i].rcTile, g_ptMouse))
			{
				if (isNoneSelect)FieldTileInfo[i].terrain = TR_NONE;
				else if (isBlockSelect)FieldTileInfo[i].terrain = TR_BLOCK;
				else if(isWaterSelect)FieldTileInfo[i].terrain = TR_WATER;
				else if(isCliffSelect)FieldTileInfo[i].terrain = TR_CLIFF;
				else if(isObjSelect)FieldTileInfo[i].terrain = TR_OBJ;
				break;// 최대한 돌지 않게;;

			}
		}
	}

	}



}


//여기 부터 캐슬 함수

void Construction::DrawSampleCastleRect()
{

	if (sampletilePosY < SAMPLECASTLETILE_X)
	{
		for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
		{
			SetRect(&sampleCastleTileInfo[i].rcTile,
				0, 0, 0, 0);
		}
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + sampletilePosX + j;
				SetRect(&sampleCastleTileInfo[printIndex].rcTile,
					j * TILESIZE*scale + (WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72, i*TILESIZE*scale + 47, j * TILESIZE*scale + TILESIZE * scale + (WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72,
					i*TILESIZE*scale + TILESIZE * scale + 47);
			}


		}
	}


}

void Construction::DrawCastleRect()
{
	for (int i = 0; i < (SAMPLECASTLETILE_Y); i++)
	{
		for (int j = 0; j < SAMPLECASTLETILE_X; j++)
		{

			SetRect(&CastleTileInfo[i*SAMPLECASTLETILE_X + j].rcTile,
				j * TILESIZE*scale, i*TILESIZE*scale, j * TILESIZE*scale + TILESIZE * scale,
				i*TILESIZE*scale + TILESIZE * scale);
		}

	}
}

void Construction::PrintCastleRect()
{
	for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
	{
		SetRect(&CastleTileInfo[i].rcTile,
			0, 0, 0, 0);
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < SAMPLECASTLETILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				{
					SetRect(&CastleTileInfo[printIndex].rcTile,
						j * (TILESIZE * scale) + 42, i*(TILESIZE*scale) + 47, j * (TILESIZE*scale) + (TILESIZE * scale) + 42,
						i* (TILESIZE*scale) + (TILESIZE * scale) + 47);

				}

			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				SetRect(&CastleTileInfo[printIndex].rcTile,
					j * TILESIZE*scale + 42, i*TILESIZE*scale + 47, j * TILESIZE*scale + 42 + TILESIZE * scale,
					i*TILESIZE*scale + TILESIZE * scale + 47);

			}
		}

	}
}

void Construction::RenderCastleTile(HDC hdc)
{
	HFONT font, oldfont;
	font = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldfont = (HFONT)SelectObject(hdc, font);
	char szText[128];
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < SAMPLECASTLETILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				Rectangle(hdc, CastleTileInfo[printIndex].rcTile.left, CastleTileInfo[printIndex].rcTile.top, CastleTileInfo[printIndex].rcTile.right, CastleTileInfo[printIndex].rcTile.bottom);
				sampleTileImage2->FrameRender(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), CastleTileInfo[printIndex].frameX, CastleTileInfo[printIndex].frameY, scale);
				if (CastleTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}
			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				/*Rectangle(hdc, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.left, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.top, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.right,
					FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.bottom);*/
				sampleTileImage2->FrameRender(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), CastleTileInfo[printIndex].frameX, CastleTileInfo[printIndex].frameY, scale);
				if (CastleTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (CastleTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, CastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), CastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}

			}
		}

	}
	//샘플 렌더



	for (int i = 0; i < TILE_Y; i++)
	{
		if (sampletilePosX < SAMPLECASTLETILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLECASTLETILE_X) + (i * SAMPLECASTLETILE_X) + sampletilePosX + j;
				sampleTileImage2->FrameRender(hdc, sampleCastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleCastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleCastleTileInfo[printIndex].frameX, sampleCastleTileInfo[printIndex].frameY, scale);

				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleCastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleCastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - sampletilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (sampletilePosY * SAMPLECASTLETILE_X) + (i * SAMPLECASTLETILE_X) + sampletilePosX + j;
				sampleTileImage2->FrameRender(hdc, sampleCastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleCastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleCastleTileInfo[printIndex].frameX, sampleCastleTileInfo[printIndex].frameY, scale);

				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleCastleTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleCastleTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
			}
		}

	}

	SelectObject(hdc, oldfont);
	DeleteObject(font);


}

void Construction::AttachCastleTile()
{
	if (!isTerraninSelect)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			cuserFrame.x = 1;
			if (!isDownSample)
			{

				for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
				{
					if (PtInRect(&sampleCastleTileInfo[i].rcTile, g_ptMouse))
					{
						/*selectTileInfo.frameX = sampleFieldTileInfo[i].frameX;
						selectTileInfo.frameY = sampleFieldTileInfo[i].frameY;*/

						selectTileInfos[0].frameX = sampleCastleTileInfo[i].frameX;
						selectTileInfos[0].frameY = sampleCastleTileInfo[i].frameY;
						isDownSample = true;
						break;// 최대한 돌지 않게;;

					}
				}
			}


		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			cuserFrame.x = 0;
			if (isDownSample)
			{
				for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
				{
					if (PtInRect(&sampleCastleTileInfo[i].rcTile, g_ptMouse))
					{
						selectTileInfos[1].frameX = sampleCastleTileInfo[i].frameX;
						selectTileInfos[1].frameY = sampleCastleTileInfo[i].frameY;
						//드래그 영역의 값을 정렬;

						minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
						maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

						dragSizeX = maxX - minX;
						dragSizeY = maxY - minY;
						isDownSample = false;
						break;// 최대한 돌지 않게;;

					}


				}
			}
			else
			{

				for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
				{
					if (PtInRect(&CastleTileInfo[i].rcTile, g_ptMouse))
					{
						for (int y = 0; y <= dragSizeY; y++)
						{
							for (int x = 0; x <= dragSizeX; x++)
							{
								if ((i%SAMPLECASTLETILE_X) + x >= SAMPLECASTLETILE_X) continue;
								if ((i / SAMPLECASTLETILE_X) + y >= (SAMPLECASTLETILE_Y)) continue;

								CastleTileInfo[i + (y* SAMPLECASTLETILE_X) + x].frameX = minX + x;
								CastleTileInfo[i + (y* SAMPLECASTLETILE_X) + x].frameY = minY + y;
							}
						}
						return;

					}

				}



			}

		}


	}
	else
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			cuserFrame.x = 1;
			for (int i = 0; i < SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y; i++)
			{
				if (PtInRect(&CastleTileInfo[i].rcTile, g_ptMouse))
				{
					if (isNoneSelect)CastleTileInfo[i].terrain = TR_NONE;
					else if (isBlockSelect)CastleTileInfo[i].terrain = TR_BLOCK;
					else if (isWaterSelect)CastleTileInfo[i].terrain = TR_WATER;
					else if (isCliffSelect)CastleTileInfo[i].terrain = TR_CLIFF;
					else if (isObjSelect)CastleTileInfo[i].terrain = TR_OBJ;
					break;// 최대한 돌지 않게;;

				}
			}
		}

	}




}




// 여기 부터 던접 맵 함수~!
void Construction::DrawSampleDungeonRect()
{
	if (sampletilePosY < SAMPLEDUNGEONTILE_Y)
	{
		for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
		{
			SetRect(&sampleDungeonTileInfo[i].rcTile,
				0, 0, 0, 0);
		}
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEDUNGEONTILE_X) + (i* SAMPLEDUNGEONTILE_X) + sampletilePosX + j;
				SetRect(&sampleDungeonTileInfo[printIndex].rcTile,
					j * TILESIZE*scale + (WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72, i*TILESIZE*scale + 47, j * TILESIZE*scale + TILESIZE * scale + (WINSIZE_X - (TILE_X*TILESIZE*scale)) - 72,
					i*TILESIZE*scale + TILESIZE * scale + 47);
			}


		}
	}
}

void Construction::DrawDungeonRect()
{
	for (int i = 0; i < SAMPLEDUNGEONTILE_Y; i++)
	{
		for (int j = 0; j < SAMPLEDUNGEONTILE_X; j++)
		{

			SetRect(&DungeonTileInfo[i*SAMPLEDUNGEONTILE_X + j].rcTile,
				j * TILESIZE*scale, i*TILESIZE*scale, j * TILESIZE*scale + TILESIZE * scale,
				i*TILESIZE*scale + TILESIZE * scale);
		}

	}
}

void Construction::PrintDungeonRect()
{
	for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
	{
		SetRect(&DungeonTileInfo[i].rcTile,
			0, 0, 0, 0);
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < SAMPLEDUNGEONTILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * SAMPLEDUNGEONTILE_X) + (i* SAMPLEDUNGEONTILE_X) + tilePosX + j;
				{
					SetRect(&DungeonTileInfo[printIndex].rcTile,
						j * (TILESIZE * scale) + 42, i*(TILESIZE*scale) + 47, j * (TILESIZE*scale) + (TILESIZE * scale) + 42,
						i* (TILESIZE*scale) + (TILESIZE * scale) + 47);

				}

			}
		}
		else
		{
			int X = SAMPLEDUNGEONTILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLEDUNGEONTILE_X) + (i* SAMPLEDUNGEONTILE_X) + tilePosX + j;
				SetRect(&DungeonTileInfo[printIndex].rcTile,
					j * TILESIZE*scale + 42, i*TILESIZE*scale + 47, j * TILESIZE*scale + 42 + TILESIZE * scale,
					i*TILESIZE*scale + TILESIZE * scale + 47);

			}
		}

	}
}

void Construction::RenderDungeonTile(HDC hdc)
{
	HFONT font, oldfont;
	font = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldfont = (HFONT)SelectObject(hdc, font);
	char szText[128];
	for (int i = 0; i < TILE_Y; i++)
	{
		if (tilePosX < SAMPLEDUNGEONTILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (tilePosY * SAMPLEDUNGEONTILE_X) + (i* SAMPLEDUNGEONTILE_X) + tilePosX + j;
			//	Rectangle(hdc, DungeonTileInfo[printIndex].rcTile.left, DungeonTileInfo[printIndex].rcTile.top, DungeonTileInfo[printIndex].rcTile.right, DungeonTileInfo[printIndex].rcTile.bottom);
				sampleTileImage3->FrameRender(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), DungeonTileInfo[printIndex].frameX, DungeonTileInfo[printIndex].frameY, scale);
				if (DungeonTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}
			}
		}
		else
		{
			int X = SAMPLEDUNGEONTILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLEDUNGEONTILE_X) + (i* SAMPLEDUNGEONTILE_X) + tilePosX + j;
				/*Rectangle(hdc, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.left, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.top, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.right,
					FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.bottom);*/
				sampleTileImage3->FrameRender(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), DungeonTileInfo[printIndex].frameX, DungeonTileInfo[printIndex].frameY, scale);
				if (DungeonTileInfo[printIndex].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (DungeonTileInfo[printIndex].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, DungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), DungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}

			}
		}

	}
	//샘플 렌더



	for (int i = 0; i < TILE_Y; i++)
	{
		if (sampletilePosX < SAMPLEDUNGEONTILE_X - 14)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEDUNGEONTILE_X) + (i * SAMPLEDUNGEONTILE_X) + sampletilePosX + j;
				sampleTileImage3->FrameRender(hdc, sampleDungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].frameX, sampleDungeonTileInfo[printIndex].frameY, scale);

				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleDungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

			}
		}
		else
		{
			int X = SAMPLEDUNGEONTILE_X - sampletilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (sampletilePosY * SAMPLEDUNGEONTILE_X) + (i * SAMPLEDUNGEONTILE_X) + sampletilePosX + j;
				sampleTileImage3->FrameRender(hdc, sampleDungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].frameX, sampleDungeonTileInfo[printIndex].frameY, scale);

				sprintf_s(szText, " %d", printIndex);
				TextOut(hdc, sampleDungeonTileInfo[printIndex].rcTile.left + (TILESIZE / 2), sampleDungeonTileInfo[printIndex].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
			}
		}

	}

	SelectObject(hdc, oldfont);
	DeleteObject(font);


}

void Construction::AttachDungeonTile()
{

	if (!isTerraninSelect)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			cuserFrame.x = 1;
			if (!isDownSample)
			{

				for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
				{
					if (PtInRect(&sampleDungeonTileInfo[i].rcTile, g_ptMouse))
					{
						/*selectTileInfo.frameX = sampleFieldTileInfo[i].frameX;
						selectTileInfo.frameY = sampleFieldTileInfo[i].frameY;*/

						selectTileInfos[0].frameX = sampleDungeonTileInfo[i].frameX;
						selectTileInfos[0].frameY = sampleDungeonTileInfo[i].frameY;
						isDownSample = true;
						break;// 최대한 돌지 않게;;

					}
				}
			}


		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			cuserFrame.x = 0;
			if (isDownSample)
			{
				for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
				{
					if (PtInRect(&sampleDungeonTileInfo[i].rcTile, g_ptMouse))
					{
						selectTileInfos[1].frameX = sampleDungeonTileInfo[i].frameX;
						selectTileInfos[1].frameY = sampleDungeonTileInfo[i].frameY;
						//드래그 영역의 값을 정렬;

						minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
						maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

						dragSizeX = maxX - minX;
						dragSizeY = maxY - minY;
						isDownSample = false;
						break;// 최대한 돌지 않게;;

					}


				}
			}
			else
			{

				for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
				{
					if (PtInRect(&DungeonTileInfo[i].rcTile, g_ptMouse))
					{
						for (int y = 0; y <= dragSizeY; y++)
						{
							for (int x = 0; x <= dragSizeX; x++)
							{
								if ((i%SAMPLEDUNGEONTILE_X) + x >= SAMPLEDUNGEONTILE_X) continue;
								if ((i / SAMPLEDUNGEONTILE_X) + y >= (SAMPLEDUNGEONTILE_Y)) continue;

								DungeonTileInfo[i + (y* SAMPLEDUNGEONTILE_X) + x].frameX = minX + x;
								DungeonTileInfo[i + (y* SAMPLEDUNGEONTILE_X) + x].frameY = minY + y;
							}
						}
						return;

					}

				}



			}

		}


	}
	else
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			cuserFrame.x = 1;
			for (int i = 0; i < SAMPLEDUNGEONTILE_X*SAMPLEDUNGEONTILE_Y; i++)
			{
				if (PtInRect(&DungeonTileInfo[i].rcTile, g_ptMouse))
				{
					if (isNoneSelect)DungeonTileInfo[i].terrain = TR_NONE;
					else if (isBlockSelect)DungeonTileInfo[i].terrain = TR_BLOCK;
					else if (isWaterSelect)DungeonTileInfo[i].terrain = TR_WATER;
					else if (isCliffSelect)DungeonTileInfo[i].terrain = TR_CLIFF;
					else if (isObjSelect)DungeonTileInfo[i].terrain = TR_OBJ;
					break;// 최대한 돌지 않게;;

				}
			}
		}

	}






}

void Construction::ChangeTerrain(TANKTERRAIN tankTerrain)
{
	//switch (tankTerrain)
	//{
	//case TTR_OBJ:
	//	break;
	//case TTR_NONE:
	//	break;
	//case TTR_R_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0* TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0* TILE_X) + 1].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1* TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1* TILE_X) + 1].terrain = TR_REDBLOCK;
	//	break;
	//case TTR_L_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
	//	break;
	//case TTR_U_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
	//	break;
	//case TTR_D_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
	//	break;
	//case TTR_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
	//	break;
	//case TTR_R_IRON:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
	//	break;
	//case TTR_L_IRON:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
	//	break;
	//case TTR_U_IRON:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
	//	break;
	//case TTR_D_IRON:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
	//	break;
	//case TTR_IRON:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_IRON;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_IRON;
	//	break;
	//case TTR_WEED:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_WEED;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_WEED;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_WEED;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_WEED;
	//	break;
	//case TTR_WATER:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_WATER;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_WATER;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_WATER;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_WATER;
	//	break;
	//case TTR_ENEMY:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_ENEMY;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_ENEMY;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_ENEMY;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_ENEMY;
	//	break;
	//case TTR_KING:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_KING;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_KING;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_KING;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_KING;
	//	break;
	//case TTR_S_L_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_REDBLOCK;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_NONE;
	//	break;
	//case TTR_S_R_REDBLOCK:
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (0 * TILE_X) + 1].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 0].terrain = TR_NONE;
	//	tileInfo[tank.posX + (tank.posY * TILE_X) + (1 * TILE_X) + 1].terrain = TR_REDBLOCK;
	//	break;
	//case TTR_END:
	//	break;
	//default:
	//	break;
	//}
}

//void Construction::ChangeRect()

	//오른쪽
	//if (tank.terrain == 1 && tank.terrain == 6)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + ((TILESIZE/2) * scale), tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	////왼쪽
	//if (tank.terrain == 2 && tank.terrain == 7)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left, tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + ((TILESIZE / 2) * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	////위에가 빈
	//if (tank.terrain == 3 && tank.terrain == 8)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left , tileInfo[tank.posY * TILE_X + tank.posX].rcTile.top + ((TILESIZE / 2) * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + (TILESIZE  * scale),
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}
	//if (tank.terrain == 4 && tank.terrain == 9)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left , tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + ((TILESIZE / 2) * scale));
	//}
	//if (tank.terrain == 5 && tank.terrain == 10)
	//{
	//	SetRect(&tileInfo[tank.posY*TILE_X + tank.posX].rcCollision,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left, tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.left + TILESIZE * scale,
	//		tileInfo[tank.posY*TILE_X + tank.posX].rcTile.top + TILESIZE * scale);
	//}



Construction::Construction()
{
}

Construction::~Construction()
{
}
