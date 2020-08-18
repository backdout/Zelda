#include "Castlemap.h"
#include "Link.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "ButtonFunc.h"
#include "Button.h"


HRESULT Castlemap::Init()
{
	bord = ImageManager::GetSingleton()->AddImage("bord2", "Image/btbord.bmp", 0, 0, 1050, 250, 1, 1, true, RGB(167, 167, 227));
	bord2 = ImageManager::GetSingleton()->AddImage("bord3", "Image/btbord.bmp", 0, 0, 260, 80, 1, 1, true, RGB(167, 167, 227));
	cuser = ImageManager::GetSingleton()->AddImage("커서", "Image/커서.bmp", 0, 0, 150, 225, 2, 3, true, RGB(68, 75, 79));
	bg = ImageManager::GetSingleton()->AddImage("샘플타일2", "Image/castlemap.bmp", 0, 0, 624, 240, SAMPLECASTLETILE_X, SAMPLECASTLETILE_Y);
	king = ImageManager::GetSingleton()->AddImage("왕", "Image/king.bmp", 0, 0, 28, 28, 1, 1, true, RGB(255, 0, 255));
	scale = 4.0f;
	cuserFrame.x = 0;
	cuserFrame.y = 0;
	if (LinkManager::GetSingleton()->GetLink() == nullptr)
	{
		link = new Link();
		LinkManager::GetSingleton()->SetLink(link);
	}
	else
	{
		link = LinkManager::GetSingleton()->GetLink();
	}
	//if(isStartVisit)
	link->Init();

	// 재방문
	if (LinkManager::GetSingleton()->GetHasNewStared())
	{
		FPOINT startPos = { 8 * 64,10 * 64 };
		// 링크 좌표 및 타일 포스 문쪽으로 설정 
		link->SetPathListClear();
		link->SetPos(startPos);
		link->SetTilePosX(1.0f);
		link->SetTilePosY(0.0f);
		// 퀘스트 번호 매니저에서 가져와 연결
		link->SetHp(LinkManager::GetSingleton()->GetLinkHert());
		link->SetMaxHp(LinkManager::GetSingleton()->GetLinkMaxHert());
		tilePosX = 1;
		tilePosY = 0;
		if (tutoScript.size()<=1)
		{
			ScriptSetting("script.txt");
		}
		scriptNum = LinkManager::GetSingleton()->GetScritpNum();
	}
	else if(LinkManager::GetSingleton()->GetHasNewStared()==false)
	{// 첫 방문
		link->Init();
		// 링크 좌표 및 타일 포스 침대쪽으로 설정
		FPOINT startPos = { 8 * 64,4 * 64 };
		// 링크 좌표 및 타일 포스 문쪽으로 설정 
		link->SetPos(startPos);
		link->SetTilePosX(21.0f);
		link->SetTilePosY(0.0f);
		
		ScriptSetting("script.txt");

		scriptNum = 0;
		hasTutorial1 = false;


		LinkManager::GetSingleton()->SetScriptNum(scriptNum);
		LinkManager::GetSingleton()->SetHasTutorial(false);
		LinkManager::GetSingleton()->SetHasStartQuest1(false);
		LinkManager::GetSingleton()->SetHasStartQuest2(false);
		LinkManager::GetSingleton()->SetHasStartQuest3(false);
		isEnding = false;
		// 퀘스트 번호 0으로 설정 


	}


	for (int i = 0; i < (SAMPLECASTLETILE_Y); i++)
	{
		for (int j = 0; j < SAMPLECASTLETILE_X; j++)
		{
			CastleTileInfo[i*SAMPLECASTLETILE_X + j].frameX = j;
			CastleTileInfo[i*SAMPLECASTLETILE_X + j].frameY = i;
		}

	}

	
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			SetRect(&PosTile[i * 18 + j].rcTile,
				j * TILESIZE*scale, i*TILESIZE*scale, j * TILESIZE*scale + TILESIZE * scale,
				i*TILESIZE*scale + TILESIZE * scale);
		}
	}



	Load();
	
	

	clickPos = { (int)(link->GetPos().x / 64),(int)(link->GetPos().y / 64) };
	link->SetClickPos(clickPos);

	link->SetIsCastleMap(true);
	link->SetIsFieldMap(false);


	ShowCursor(false);
	SetRect(&scriptZone, 20, 640, 1070, 890);
	CastleTileInfo[126].hasItem = true;
	return S_OK;
}

void Castlemap::Release()
{





}

void Castlemap::Update()
{
	PrintRect();

	link->Update();

	linkPos = link->GetPos();

	tilePosX = link->GetTilePosX();
	tilePosY = link->GetTilePosY();

	LinkAtt();
	
	
	MoveClickCheck();


	if (link->GetPathList().size() > 0)
	{
		moveTime += TimeManager::GetSingleton()->GetDeltaTime();

		if (link->GetIsRollingMove())
		{
			if (moveTime >= 0.08f)
			{
				link->SetIsMove(true);
				moveTime -= 0.08f;
			}
		}
		else
		{
			if (moveTime >= 0.12f)
			{
				link->SetIsMove(true);
				moveTime -= 0.12f;
			}
		}
	}

	
	printIndex = 0;
	if (tilePosX == 0 || tilePosX == 1 || tilePosX == 2)
	{
		if (link->GetLinkIndexPos().x == 8 && link->GetLinkIndexPos().y == 11)
		{		
			if (LinkManager::GetSingleton()->GetIsLoadField())
			{
				link->SetPathListClear();
				//LinkManager::GetSingleton()->SetIsLoadField(false);
				LinkManager::GetSingleton()->SetLinkHert(link->GetHp());
				LinkManager::GetSingleton()->SetLinkMaxHert(link->GetMaxHp());
				SceneManager::GetSingleton()->LoadingChangeScene("로드필드", "로딩1");
				return;
			}
			else if (LinkManager::GetSingleton()->GetIsLoadField() == false|| LinkManager::GetSingleton()->GetHasNewStared()==false)
			{
				link->SetPathListClear();
				LinkManager::GetSingleton()->SetLinkHert(link->GetHp());
				LinkManager::GetSingleton()->SetLinkMaxHert(link->GetMaxHp());
				SceneManager::GetSingleton()->LoadingChangeScene("필드", "로딩1");
				return;
			}
			
		}
	}
	QuestClickCheck();
	Tutorial();
	Quest1();
	Quest2();
	Quest3();
	Ending();

}

void Castlemap::Render(HDC hdc)
{
	MapRender(hdc);
	
	if (link)link->Render(hdc);
	
	for (int i = 0; i < TILE_Y + 1; i++)
	{
		if (tilePosX < SAMPLECASTLETILE_X - 14)
		{
			for (int j = 0; j < TILE_X + 4; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				if (PosTile[i * (TILE_X + 4) + j].terrain == TR_OBJ)
				{
					bg->FrameRender(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].frameX, PosTile[i * (TILE_X + 4) + j].frameY, scale);
				}
				if (PosTile[i * (TILE_X + 4) + j].hasItem == true)
				{
					king->Render(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left, PosTile[i * (TILE_X + 4) + j].rcTile.top,4.0f);
				}
			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				if (PosTile[i * (TILE_X + 4) + j].terrain == TR_OBJ)
				{
					bg->FrameRender(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].frameX, PosTile[i * (TILE_X + 4) + j].frameY, scale);
				}
				if (PosTile[i * (TILE_X + 4) + j].hasItem == true)
				{
					king->Render(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left, PosTile[i * (TILE_X + 4) + j].rcTile.top, 4.0f);
				}

			}
		}

	}

	
	if (isQuestPrint)
	{
		
		bord->Render(hdc, 20, 640);
		font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, "궁서");
		oldfont = (HFONT)SelectObject(hdc, font);
		szText[128];
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT); //배경색 지우기
		if (!isEnding)
		{
			sprintf_s(szText, "[하이랄 왕]");
			
		}
		else
		{
			sprintf_s(szText, "[던전 찾는 개발자]");
		}
		TextOut(hdc, 70, 670, szText, strlen(szText));
		sprintf_s(szText,printScript.c_str());
		TextOut(hdc, 70, 700, szText, strlen(szText));
		sprintf_s(szText, "Click!!");
		TextOut(hdc, 900, 820, szText, strlen(szText));
		SelectObject(hdc, oldfont);
		DeleteObject(font);
	}
	QuestStatus(hdc);
	cuser->FrameRender(hdc, g_ptMouse.x + (cuser->GetFrameWidth() / 2), g_ptMouse.y + (cuser->GetFrameHeight() / 2), cuserFrame.x, cuserFrame.y);
}

void Castlemap::Load()
{

	DWORD readByte;
	HANDLE hFile = CreateFile("Save/Castle.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, CastleTileInfo, sizeof(TILE_INFO)*SAMPLECASTLETILE_X*SAMPLECASTLETILE_Y, &readByte, NULL);
	CloseHandle(hFile);

}

void Castlemap::Save()
{




}

void Castlemap::PrintRect()
{

	for (int i = 0; i < TILE_Y + 1; i++)
	{
		if (tilePosX < SAMPLECASTLETILE_X - 14)
		{
			for (int j = 0; j < TILE_X + 4; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;

				PosTile[i * (TILE_X + 4) + j] = CastleTileInfo[printIndex];

				SetRect(&PosTile[i * (TILE_X + 4) + j].rcTile,
					j * TILESIZE*scale, i*TILESIZE*scale, j * TILESIZE*scale + TILESIZE * scale,
					i*TILESIZE*scale + TILESIZE * scale);
				PosTile[i * (TILE_X + 4) + j].terrain = CastleTileInfo[printIndex].terrain;
				if (CastleTileInfo[printIndex].enemy == nullptr)	PosTile[i * (TILE_X + 4) + j].enemy = nullptr;
				else PosTile[i * (TILE_X + 4) + j].enemy = CastleTileInfo[printIndex].enemy;


				//if ((i >= 2 && i < 11) && (j >= 3 && j < 13) && PosTile[(i * 18) + j].enemy != nullptr)
				//{
				//	PosTile[(i * 18) + j].enemy->SetIsLinkArea(true);
				//	enemyMgr->SetTileInfo(PosTile);
				//}
				//else if ((i < 2 || i >= 11 || j < 3 || j >= 13) && PosTile[(i * 18) + j].enemy != nullptr)//else if (!((i >= 3 && i < 10) && (j >= 5 && j < 12)) && PosTile[(i * 18) + j].enemy != nullptr)
				//{
				//	PosTile[(i * 18) + j].enemy->SetIsLinkArea(false);
				//}


			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;

				SetRect(&PosTile[i * (TILE_X + 4) + j].rcTile,
					j * TILESIZE*scale, i*TILESIZE*scale, j * TILESIZE*scale + TILESIZE * scale,
					i*TILESIZE*scale + TILESIZE * scale);
				PosTile[i * (TILE_X + 4) + j] = CastleTileInfo[printIndex];
				PosTile[i * (TILE_X + 4) + j].terrain = CastleTileInfo[printIndex].terrain;

				/*if (FieldTileInfo[printIndex].enemy == nullptr)	PosTile[i * (TILE_X + 4) + j].enemy = nullptr;
				else PosTile[i * (TILE_X + 4) + j].enemy = FieldTileInfo[printIndex].enemy;

				if ((i >= 2 && i < 11) && (j >= 3 && j < 13) && PosTile[(i * 18) + j].enemy != nullptr)
				{
					PosTile[(i * 18) + j].enemy->SetIsLinkArea(true);
				}
				else if ((i < 2 || i >= 11 || j < 3 || j >= 13) && PosTile[(i * 18) + j].enemy != nullptr)
				{
					PosTile[(i * 18) + j].enemy->SetIsLinkArea(false);
				}*/



			}
		}

	}



}

void Castlemap::MapRender(HDC hdc)
{

	for (int i = 0; i < TILE_Y + 1; i++)
	{
		if (tilePosX < FIELDTILE_X_2 - 14)
		{
			for (int j = 0; j < TILE_X + 4; j++)
			{
				//printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				//Rectangle(hdc, FieldTileInfo[printIndex].rcTile.left, FieldTileInfo[printIndex].rcTile.top, FieldTileInfo[printIndex].rcTile.right, FieldTileInfo[printIndex].rcTile.bottom);
				//bg->FrameRender(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), FieldTileInfo[printIndex].frameX, FieldTileInfo[printIndex].frameY, scale);
				bg->FrameRender(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].frameX, PosTile[i * (TILE_X + 4) + j].frameY, scale);

				/*if (PosTile[i * (TILE_X + 4) + j].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}*/
			}
		}
		else
		{
			int X = SAMPLECASTLETILE_X - tilePosX;
			for (int j = 0; j < X; j++)
			{
				//printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
				bg->FrameRender(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].frameX, PosTile[i * (TILE_X + 4) + j].frameY, scale);

				//Rectangle(hdc, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.left, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.top, FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.right,
					//FieldTileInfo[(tileframeY + i)* FIELDTILE_X_1 + tileframeX + j].rcTile.bottom);*/
				//bg->FrameRender(hdc, FieldTileInfo[printIndex].rcTile.left + (TILESIZE / 2), FieldTileInfo[printIndex].rcTile.top + (TILESIZE / 2), FieldTileInfo[printIndex].frameX, FieldTileInfo[printIndex].frameY, scale);
				/*if (PosTile[i * (TILE_X + 4) + j].terrain == TR_BLOCK)
				{
					SetTextColor(hdc, RGB(237, 28, 36));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_WATER)
				{
					SetTextColor(hdc, RGB(63, 72, 204));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_CLIFF)
				{
					SetTextColor(hdc, RGB(140, 24, 113));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else if (PosTile[i * (TILE_X + 4) + j].terrain == TR_OBJ)
				{
					SetTextColor(hdc, RGB(255, 255, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));
				}
				else
				{

					SetTextColor(hdc, RGB(0, 0, 0));
					sprintf_s(szText, " %d", printIndex);
					TextOut(hdc, PosTile[i * (TILE_X + 4) + j].rcTile.left + (TILESIZE / 2), PosTile[i * (TILE_X + 4) + j].rcTile.top + (TILESIZE / 2), szText, strlen(szText));

				}*/

			}
		}

	}

}

void Castlemap::LinkAtt()
{
	if (link->GetIshit())
	{
		link->SetIshit(false);
		movePoint.x = (linkPos.x / 64);
		movePoint.y = (linkPos.y / 64);
		if (movePoint.x != 0 && link->GetMovestate() == LEFT && PosTile[movePoint.y * 18 + movePoint.x].enemy != nullptr)
		{
			if (PosTile[movePoint.y * 18 + movePoint.x].enemy->GetIsDie() == false)
			{
				PosTile[movePoint.y * 18 + movePoint.x].enemy->SetHitCount(PosTile[movePoint.y * 18 + movePoint.x].enemy->GetHitCount() - 1);

			}
		}


		if (movePoint.x != 17 && link->GetMovestate() == RIGHT && PosTile[movePoint.y * 18 + movePoint.x + 1].enemy != nullptr)
		{
			if (PosTile[movePoint.y * 18 + movePoint.x + 1].enemy->GetIsDie() == false)
			{
				PosTile[movePoint.y * 18 + movePoint.x + 1].enemy->SetHitCount(PosTile[movePoint.y * 18 + movePoint.x + 1].enemy->GetHitCount() - 1);
			}
		}


		if (movePoint.y != 14 && link->GetMovestate() == BOTTOM && PosTile[((movePoint.y + 1) * 18) + movePoint.x].enemy != nullptr)
		{
			if (PosTile[((movePoint.y + 1) * 18) + movePoint.x].enemy->GetIsDie() == false)
			{
				PosTile[((movePoint.y + 1) * 18) + movePoint.x].enemy->SetHitCount(PosTile[((movePoint.y + 1) * 18) + movePoint.x].enemy->GetHitCount() - 1);
			}
		}


		if (movePoint.y != 0 && link->GetMovestate() == TOP && PosTile[((movePoint.y) * 18) + movePoint.x].enemy != nullptr)
		{
			if (PosTile[((movePoint.y) * 18) + movePoint.x].enemy->GetIsDie() == false)
			{
				PosTile[((movePoint.y) * 18) + movePoint.x].enemy->SetHitCount(PosTile[((movePoint.y) * 18) + movePoint.x].enemy->GetHitCount() - 1);
			}
		}


	}

}

void Castlemap::MoveClickCheck()
{
	if(!isQuestPrint)
	{
	for (int i = 0; i < TILE_Y + 1; i++)
	{
		{
			for (int j = 0; j < TILE_X + 4; j++)
			{
				//Rectangle(hdc, FieldTileInfo[printIndex].rcTile.left, FieldTileInfo[printIndex].rcTile.top, FieldTileInfo[printIndex].rcTile.right, FieldTileInfo[printIndex].rcTile.bottom);
				
				if (PtInRect(&PosTile[i * 18 + j].rcTile, g_ptMouse))
				{
				
					if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
					{
						printIndex = (tilePosY * SAMPLECASTLETILE_X) + (i* SAMPLECASTLETILE_X) + tilePosX + j;
						if (printIndex == 126)
						{
							isQuestPrint = true;
							break;
						}

						if (i == 0 && j == 16)continue;
						//if (link->GetHasClick()==false)
						{
							if (PosTile[i * 18 + j].terrain == TR_NONE || PosTile[i * 18 + j].terrain == TR_OBJ)
							{
								if (!(link->GetLinkIndexPos().x == j && link->GetLinkIndexPos().y == i))
								{
									link->SetHasClick(true);
									rotationX = j; rotationY = i;
									mouseIndex = i * 18 + j;
									clickPos.x = j;
									clickPos.y = i;
									link->SetIsRollingMove(false);
									link->SetTileInfo(PosTile);
									link->SetClickPos(clickPos);
									link->SetCurrPos(tilePosX, tilePosY);
								}
								//link->SetHasAttack(false);

							}
						}
						cuserFrame.x = 1;
						break;
					}
					else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
					{
						if (i == 0 && j == 16)continue;
						cuserFrame.x = 1;
						if (PosTile[i * 18 + j].terrain == TR_NONE || PosTile[i * 18 + j].terrain == TR_OBJ)
						{
							if (!(link->GetLinkIndexPos().x == j && link->GetLinkIndexPos().y == i))
							{
								link->SetHasClick(true);
								rotationX = j; rotationY = i;
								mouseIndex = i * 18 + j;
								clickPos.x = j;
								clickPos.y = i;
								link->SetIsRollingMove(true);
								link->SetTileInfo(PosTile);
								link->SetClickPos(clickPos);
								link->SetCurrPos(tilePosX, tilePosY);
								//link->SetHasAttack(false);
							}
						}
						break;
					}
					else
					{
						cuserFrame.x = 0;
						if (PosTile[i * 18 + j].terrain == TR_NONE || PosTile[i * 18 + j].terrain == TR_OBJ)
						{
							cuserFrame.y = 0;
						}
						else if (PosTile[i * 18 + j].hasItem == true)
						{
							cuserFrame.y = 2;
						}
						else
						{
							cuserFrame.y = 1;
						}
					}
				}

			}
		}
	}

}


}

void Castlemap::ScriptSetting(string fileName)
{

	tutoScript.clear();
	questScript1.clear();
	questScript2.clear();
	questScript3.clear();
	ending.clear();
	ifstream fin;

	fin.open(fileName);
	string 	script;
	while (script!="튜토리얼")
	{
		getline(fin, script);
		if (script != "튜토리얼")
		{
			tutoScript.push_back(script);
		}
	}
	
	getline(fin, questClearNum);
	LinkManager::GetSingleton()->SetQuestClearNum1(atoi(questClearNum.c_str()));
	while (script != "퀘스트1")
	{
		getline(fin, script);
		if (script != "퀘스트1")
		{
			questScript1.push_back(script);
		}
	}
	getline(fin, questClearNum);
	LinkManager::GetSingleton()->SetQuestClearNum2(atoi(questClearNum.c_str()));
	while (script != "퀘스트2")
	{
		getline(fin, script);
		if (script != "퀘스트2")
		{
			questScript2.push_back(script);
		}
	}
	getline(fin, questClearNum);
	LinkManager::GetSingleton()->SetQuestClearNum3(atoi(questClearNum.c_str()));
	while (script != "퀘스트3")
	{
		getline(fin, script);
		if (script != "퀘스트3")
		{
			questScript3.push_back(script);
		}
	}
	while (script != "엔딩")
	{
		getline(fin, script);
		if (script != "엔딩")
		{
			ending.push_back(script);
		}
	}

}

void Castlemap::QuestClickCheck()
{
	if (!isQuestPrint)
	{
		for (int i = 0; i < 9; i++)
		{
			if (tilePosX == i)
			{
				if (PtInRect(&PosTile[4 * 18 + (9 - i)].rcTile, g_ptMouse))
				{
					if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
					{
						isQuestPrint = true;
					}
				}
			}
		}
	}

}

void Castlemap::Tutorial()
{

	//튜토리얼 false  일때 시작 if()
	if (LinkManager::GetSingleton()->GetHasTutorial() == false)
	{
		//1 번째
		if (!hasTutorial1)
		{
			scriptTime += TimeManager::GetSingleton()->GetDeltaTime();
			printScript = tutoScript[scriptNum];
			if (scriptTime >= 1.0f)
			{
				isQuestPrint = true;
			}
		}
		if (isQuestPrint)
		{
			printScript = tutoScript[scriptNum];
			cuserFrame.x = 0;
			cuserFrame.y = 0;
			if (PtInRect(&scriptZone, g_ptMouse))
			{
				if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
				{
					
					if (!hasTutorial1)
					{
						if (2 > scriptNum)
						{
							scriptNum++;
						}
						else
						{
							isQuestPrint = false;
							hasTutorial1 = true;
							scriptNum++;

						}
					}
					else
					{
						if (tutoScript.size()-1 > scriptNum)
						{
							scriptNum++;
							
						}
						else {

							isQuestPrint = false;
							LinkManager::GetSingleton()->SetHasTutorial(true);
							scriptNum = 0;
						}
					}
				}
			}
		}
	}

}

void Castlemap::Quest1()
{
	if (isQuestPrint&&LinkManager::GetSingleton()->GetHasTutorial()&& LinkManager::GetSingleton()->GetHasQuest1()==false)
	{
		if ((LinkManager::GetSingleton()->GetQuestClearNum1()) <= LinkManager::GetSingleton()->GetQuestCount1())
		{
			isQuestPrint = true;
			LinkManager::GetSingleton()->SetHasQuest1(true);
			scriptNum = 0;
			printScript = questScript2[scriptNum];
			scriptNum++;
			return;
		}

		printScript = questScript1[scriptNum];
		cuserFrame.x = 0;
		cuserFrame.y = 0;
		if (PtInRect(&scriptZone, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				
			
				if (questScript1.size() - 1 > scriptNum)
				{
					scriptNum++;

				}
				if (questScript1.size() - 1 <= scriptNum) {
			
					//LinkManager::GetSingleton()->SetHasTutorial(true);
					LinkManager::GetSingleton()->SetScriptNum(scriptNum);
					LinkManager::GetSingleton()->SetHasStartQuest1(true);
					isQuestPrint = false;
					



				}
				

			}
		}
	}




}


void Castlemap::Quest2()
{
	if (isQuestPrint&&LinkManager::GetSingleton()->GetHasQuest1() && LinkManager::GetSingleton()->GetHasQuest2() == false)
	{

		if ((LinkManager::GetSingleton()->GetQuestClearNum2()) <= LinkManager::GetSingleton()->GetQuestCount2())
		{
			isQuestPrint = true;
			LinkManager::GetSingleton()->SetHasQuest2(true);
			scriptNum = 0;
			printScript = questScript3[scriptNum];
			scriptNum++;
			return;
		}


		printScript = questScript2[scriptNum];
		cuserFrame.x = 0;
		cuserFrame.y = 0;
		if (PtInRect(&scriptZone, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{

				{
					if (questScript2.size() - 1 > scriptNum)
					{
						scriptNum++;

					}
					if (questScript2.size() - 1 <= scriptNum) {

						LinkManager::GetSingleton()->SetHasStartQuest2(true);
						LinkManager::GetSingleton()->SetScriptNum(scriptNum);
						isQuestPrint = false;

						//LinkManager::GetSingleton()->SetHasTutorial(true);
					}
				}
			}
		}
	}



}

void Castlemap::Quest3()
{

	if (isQuestPrint&&LinkManager::GetSingleton()->GetHasQuest2() && LinkManager::GetSingleton()->GetHasQuest3() == false)
	{

		if (LinkManager::GetSingleton()->GetQuestClearNum3() == LinkManager::GetSingleton()->GetQuestCount3())
		{
			LinkManager::GetSingleton()->SetHasQuest3(true);
			scriptNum = 0;
			printScript = ending[scriptNum];
			scriptNum++;
			return;
		}

		printScript = questScript3[scriptNum];
		cuserFrame.x = 0;
		cuserFrame.y = 0;
		if (PtInRect(&scriptZone, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				
				{
					if (questScript3.size() - 1 > scriptNum)
					{
						scriptNum++;

					}
					if (questScript3.size() - 1 <= scriptNum) {

						LinkManager::GetSingleton()->SetHasStartQuest3(true);
						LinkManager::GetSingleton()->SetScriptNum(scriptNum);
						isQuestPrint = false;
					
					}
				}
			}
		}
	}


}

void Castlemap::Ending()
{

	if (isQuestPrint&&LinkManager::GetSingleton()->GetHasQuest3())
	{

		

		printScript = ending[scriptNum];
		cuserFrame.x = 0;
		cuserFrame.y = 0;
		if (PtInRect(&scriptZone, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{

				{
					if (ending.size() - 1 > scriptNum)
					{
						scriptNum++;

					}
					if (ending.size() - 1 <= scriptNum) {
						printScript = ending[scriptNum];
						if (!isEnding)
						{
							isEnding = true;
							return;
						}
						else 
						{
							isQuestPrint = false;
							SceneManager::GetSingleton()->LoadingChangeScene("타이틀", "로딩1");
							return;
						}
						//isQuestPrint = false;

					}
				}
			}
		}
	}



}

void Castlemap::QuestStatus(HDC hdc)
{
	if ( LinkManager::GetSingleton()->GetHasQuest1() == false&& LinkManager::GetSingleton()->GetHasStartQuest1())
	{
		bord2->Render(hdc, 835, 90);
		font = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, "궁서");
		oldfont = (HFONT)SelectObject(hdc, font);
		szText[128];
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT); //배경색 지우기
		sprintf_s(szText, "[퀘스트 : 첫번째 시련]");
		TextOut(hdc, 850, 100, szText, strlen(szText));
		sprintf_s(szText, "귀여운(?) 미라군을 잡아줘~!");
		TextOut(hdc, 850, 120, szText, strlen(szText));
		sprintf_s(szText, "미라군 ( %d / %d)", LinkManager::GetSingleton()->GetQuestCount1(), LinkManager::GetSingleton()->GetQuestClearNum1());
		TextOut(hdc, 850, 140, szText, strlen(szText));
		SelectObject(hdc, oldfont);
		DeleteObject(font);


	}


	if (LinkManager::GetSingleton()->GetHasQuest2() == false && LinkManager::GetSingleton()->GetHasStartQuest2())
	{
		bord2->Render(hdc, 835, 90);
		font = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, "궁서");
		oldfont = (HFONT)SelectObject(hdc, font);
		szText[128];
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT); //배경색 지우기
		sprintf_s(szText, "[퀘스트 : 두번째 시련]");
		TextOut(hdc, 850, 100, szText, strlen(szText));
		sprintf_s(szText, "황색 돼... 아니 오크를 잡아줘~!");
	                    ///   귀여운(?) 미라군을 잡아줘~!
		TextOut(hdc, 850, 120, szText, strlen(szText));
		sprintf_s(szText, "황색 오크 ( %d / %d)", LinkManager::GetSingleton() ->GetQuestCount2(), LinkManager::GetSingleton()->GetQuestClearNum2());
		TextOut(hdc, 850, 140, szText, strlen(szText));
		SelectObject(hdc, oldfont);
		DeleteObject(font);

	}

	if (LinkManager::GetSingleton()->GetHasQuest3() == false && LinkManager::GetSingleton()->GetHasStartQuest3())
	{
		bord2->Render(hdc, 835, 90);
		font = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, "궁서");
		oldfont = (HFONT)SelectObject(hdc, font);
		szText[128];
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT); //배경색 지우기
		sprintf_s(szText, "[퀘스트 : 마지막 시련]");
		TextOut(hdc, 850, 100, szText, strlen(szText));
		sprintf_s(szText, "파란 오크를 싹Three해줘~!");
		                   
		TextOut(hdc, 850, 120, szText, strlen(szText));
		sprintf_s(szText, "파란 오크 ( %d / %d)", LinkManager::GetSingleton()->GetQuestCount3(), LinkManager::GetSingleton()->GetQuestClearNum3());
		TextOut(hdc, 850, 140, szText, strlen(szText));
		SelectObject(hdc, oldfont);
		DeleteObject(font);


	}

}

Castlemap::Castlemap()
{
}

Castlemap::~Castlemap()
{
}
