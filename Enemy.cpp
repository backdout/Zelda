#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Animation.h"
#include "pch.h"
#include "Link.h"
#include "Missile.h"
#include "AStarTile.h"

HRESULT Enemy::Init()
{

//	isDie = false;
	isAttMode = false;


	pos = { 0, 0 };
	tileInfo = new TILE_INFO[TILE_X* TILE_Y];

	playAni->Start();	//Load();
	pos.x = tileInfo[0].rcTile.left;
	pos.y = tileInfo[0].rcTile.top;
	AttSetting = false;
	return S_OK;
}


HRESULT Enemy::Init(int _indexNum)//, int enemyNum)
{
	//isDie = false;
	//	typeNum = enemyNum;
		//pos.x = posX;
		//pos.y = posY;
		//tileInfo = new TILE_INFO[TILE_X* TILE_Y];
		//Load();
		// (tilePosY * FIELDTILE_X_2) + (i* FIELDTILE_X_2) + tilePosX + j;
	fieldTileInfo[_indexNum].enemy = this;
	indexNum = _indexNum;
	posIndex.x = _indexNum % FIELDTILE_X_2;
	posIndex.y = _indexNum / FIELDTILE_X_2;
	pos.x = posIndex.x * 64 + movePos.x;;
	pos.y = posIndex.x * 64 + movePos.y;;



	if (typeNum == 0)
	{
		moveImg = ImageManager::GetSingleton()->AddImage("enemy1", "Image/몬스터1이동.bmp", pos.x, pos.y, 192, 160, 4, 4, true, RGB(192, 192, 192));
		attImg = ImageManager::GetSingleton()->AddImage("enemy1공격", "Image/몬스터1공격.bmp", pos.x, pos.y, 256, 192, 4, 4, true, RGB(192, 192, 192));
	}
	else if (typeNum == 1)
	{
		moveImg = ImageManager::GetSingleton()->AddImage("enemy2", "Image/몬스터2이동.bmp", pos.x, pos.y, 192, 160, 4, 4, true, RGB(255, 0, 255));
		attImg = ImageManager::GetSingleton()->AddImage("enemy2공격", "Image/몬스터2공격.bmp", pos.x, pos.y, 256, 192, 4, 4, true, RGB(192, 192, 192));
	}
	else if (typeNum == 2)
	{
		moveImg = ImageManager::GetSingleton()->AddImage("enemy3", "Image/몬스터3이동.bmp", pos.x, pos.y, 336, 160, 7, 4, true, RGB(164, 128, 255));//RGB(255, 0, 255));
		attImg = ImageManager::GetSingleton()->AddImage("enemy3공격", "Image/몬스터3공격.bmp", pos.x, pos.y, 384, 192, 6, 4, true, RGB(164, 128, 255));
	}

	hitcount = 3;
	tempHitcount = hitcount;
	isAttMode = false;
	hasEnemy = false;
	actEnemy = false;
	hasItem = false;
	isLinkArea = false; //해당 경우 몬스터가 있는 타일만 해당 
	hasHitting = false;// 몬스터가 활성화 되어 있을때만 가능

	startTile = new AStarTile();

	endTile = new AStarTile();
	minH = 99999;
	lastMinTile = nullptr;

	currTile = startTile;

	tiles.reserve(ASTAR_TILE_NUM_Y * ASTAR_TILE_NUM_X);

	for (int i = 0; i < TILE_Y + 1; i++)
	{
		for (int j = 0; j < TILE_X + 4; j++)
		{

			AStarTile* tile = new AStarTile();
			tile->Init(j, i);
			tiles.push_back(tile);

		}
	}




	//0~3 top /4~7 left/8~11 right/12~15bottom
	moveAni = new Animation();
	moveAni->Init(moveImg->GetWidth(), moveImg->GetHeight(), moveImg->GetFrameWidth(), moveImg->GetFrameHeight());
	moveAni->SetUpdateTime(FPS / 10.0);
	moveAni->SetPlayFrame(0, 3, true, true);

	attAni = new Animation();
	attAni->Init(attImg->GetWidth(), attImg->GetHeight(), attImg->GetFrameWidth(), attImg->GetFrameHeight());
	attAni->SetUpdateTime(FPS / 10.0);
	attAni->SetPlayFrame(0, 3, true, false);

	playAni = moveAni;
	playAni->Start();
	AttSetting = false;
	isFirstAtt = true;
	//	MovePath(posX, posY);
	return S_OK;
}


void Enemy::Release()
{


	SAFE_DELETE(attAni);
	SAFE_DELETE(moveAni);
	/*SAFE_DELETE(enemyLeft);
	SAFE_DELETE(enemyRight);*/
}

void Enemy::Update()
{
	if (!isDie)
	{
		posIndex.x = (indexNum % FIELDTILE_X_2) - tilePosX;
		posIndex.y = (indexNum / FIELDTILE_X_2) - tilePosY;
		if (hitcount < tempHitcount)
		{
			if (hitTime <= 0)
			{
				hitLoop = true;
			}

			hitTime += TimeManager::GetSingleton()->GetDeltaTime();
			if (hitLoop)
			{
				if (hitTime >= 0.1f&&hitTime < 0.15f)
				{
					hitLoop = false;
				}
				if (hitTime >= 0.30f&&hitTime < 0.45f)
				{
					hitLoop = false;
				}
				if (hitTime >= 0.60f&&hitTime < 0.75f)
				{
					hitLoop = false;
				}
				if (hitTime >= 0.90f&&hitTime < 1.05f)
				{
					hitLoop = false;
				}
			}
			else
			{
				if (hitTime >= 0.15f&&hitTime < 0.30f)
				{
					hitLoop = true;
				}
				if (hitTime >= 0.45f&&hitTime < 0.60f)
				{
					hitLoop = true;
				}
				if (hitTime >= 0.75f&&hitTime < 0.90f)
				{
					hitLoop = true;
				}
			}

			if (hitTime >= 1.2f)
			{
				hitTime = 0;
				hitLoop = false;
				tempHitcount = hitcount;
			}
			if (tempHitcount <= 0)
			{
				isDie = true;
				if (typeNum == 0)
				{
					LinkManager::GetSingleton()->SetQuestCount3(LinkManager::GetSingleton()->GetQuestCount3() + 1);
				}
				else if (typeNum == 1)
				{
					LinkManager::GetSingleton()->SetQuestCount2(LinkManager::GetSingleton()->GetQuestCount2() + 1);
				}
				else if (typeNum == 2)
				{
					LinkManager::GetSingleton()->SetQuestCount1(LinkManager::GetSingleton()->GetQuestCount1() + 1);
				}

			}
		}

		if (posIndex.x >= 0 && posIndex.x < 18 && posIndex.y >= 0 && posIndex.y < 15)
		{
			pos.x = posIndex.x * 64 + movePos.x;
			pos.y = posIndex.y * 64 + movePos.y;
		}
		else
		{
			actEnemy = false;
			isFirstAtt = true;
		}


		if (actEnemy&&isLinkArea)
		{
			iswaitTime = false;
			FindPathTime += TimeManager::GetSingleton()->GetDeltaTime();
			moveTime += TimeManager::GetSingleton()->GetDeltaTime();

			if (FindPathTime >= 1.5f || isFirstAtt)
			{
				isFirstAtt = false;
				pathList.clear();
				for (int i = 0; i < ASTAR_TILE_NUM_Y*ASTAR_TILE_NUM_X; i++)
				{
					{
						tiles[i]->SetAttribute(tileInfo[i].terrain);
					}
				}

				startTile->Init(posIndex.x, posIndex.y);
				tiles[posIndex.y*ASTAR_TILE_NUM_X + posIndex.x]->SetAttribute(TR_ENEMYSTARTTILE);
				linkIndexPos = link->GetLinkIndexPos();
				endTile->Init(linkIndexPos.x, linkIndexPos.y);
				tiles[linkIndexPos.y*ASTAR_TILE_NUM_X + linkIndexPos.x]->SetAttribute(TR_ENEMYENDTILE);
			
				currTile = startTile;
				
				minH = 99999;
				lastMinTile = nullptr;
				AstarPath(currTile);
				playAni->Stop();

				fixlinkIndexPos = posIndex;
				FindPathTime -= 1.5f;
				
			}
			if (pathList.size() > 0)
			{
				isAttMode = false;
				if (moveTime > 0.5f)
				{
					MovePathCheck();
					moveTime = 0;
				}
			}//pathList.size() <= 0||// 공격 모션이랑 무브 모션이 겹쳐서 제외 시킴
			else if ((pos.x > link->GetPos().x&&pos.y == link->GetPos().y) ||
				(pos.x < link->GetPos().x&&pos.y == link->GetPos().y) ||
				(pos.y > link->GetPos().y && pos.x == link->GetPos().x) ||
				(pos.y < link->GetPos().y&& pos.x == link->GetPos().x))
			{
				//공격 모션으로
				if (!isAttMode)
				{
					enemystate = MOVE_END;
					isAttMode = true;
				}
				AttMotion();
				AttCheck();
			}

		}
		if (!isLinkArea)
		{
			// 이동을 멈추고, A*  및 이동 리스트 초기화 
			pathList.clear();
			// 범위에서 벗어나면 정면을 보고 걷기 
			iswaitTime = true;
			isAttMode = false;
			MovePathCheck();

		}

		playAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}
}

void Enemy::Render(HDC hdc)
{

	if (!isDie && actEnemy)
	{
		if (isAttMode) attImg->AnimationRender(hdc, pos.x - (attImg->GetFrameWidth() / 2), pos.y - (attImg->GetFrameHeight() / 2), playAni, 3.0f, hitLoop);
		else moveImg->AnimationRender(hdc, pos.x, pos.y, playAni, 3.0f, hitLoop);
	}
	//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
}


void Enemy::Load()
{

	DWORD readByte;
	HANDLE hFile = CreateFile("Save/newfile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, tileInfo, sizeof(TILE_INFO)*TILE_X*TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void Enemy::MovePath(int x, int y)
{
	
}

void Enemy::AstarPath(AStarTile* currentTile)
{
	if (hasPath)
	{
		pathList.clear();
		hasPath = false;
		enemystate = MOVE_END;
	}
	AddOpenList(currentTile);

	if (openList.size() ==0 )
	{
		AStarTile* curr = lastMinTile->GetParentTile();
		POINT listPos = currPos;

		while (curr->GetParentTile() != nullptr)
		{
			listPos.x = curr->GetIdX() - curr->GetParentTile()->GetIdX();
			listPos.y = curr->GetIdY() - curr->GetParentTile()->GetIdY();
			pathList.push_back(listPos);
			curr = curr->GetParentTile();
		}

		openList.clear();
		closeList.clear();
		isOneTile = false;
		hasPath = true;
		playAni->Start();
		tiletX = posIndex.x;
		tiletY = posIndex.y;
		return;
	}

	float minF = 99999;
	AStarTile* minTile = nullptr;
	int F, G, H;
	for (int i = 0; i < openList.size(); i++)
	{
		//도착지점까지의 예상 비용 계산
		H = abs(endTile->GetIdX() - openList[i]->GetIdX()) + abs(endTile->GetIdY() - openList[i]->GetIdY()) * 10;

		openList[i]->SetCostToGoal(H);

		// 시작 타일부터 현재 타일까지의 비용 계산
		// 부모 타일의 G + 타일 하나의 이동 비용
		AStarTile* parent = openList[i]->GetParentTile();
		if (parent)
		{
			G = parent->GetCostFromStart() +
				GetDistance(parent->GetPos().x, parent->GetPos().y,
					openList[i]->GetPos().x, openList[i]->GetPos().y) > ASTAR_TILE_WIDTH ? 14 : 10;
		}
		else
		{
			G = GetDistance(parent->GetPos().x, parent->GetPos().y,
				openList[i]->GetPos().x, openList[i]->GetPos().y) > ASTAR_TILE_WIDTH ? 14 : 10;
		}

		openList[i]->SetCostFromStart(G);

		F = G + H;
		openList[i]->SetTotalCost(F);

		// 가장 비용이 적게 드는 타일을 선택한다.
		if (minF > F)
		{
			minF = F;
			minTile = openList[i];
		}

		if (minH >H)
		{
			minH = H;
			lastMinTile = openList[i];
		}

	}



	// 가장 적은 비용이 드는 타일이 도착지점일 경우
	if (minTile->GetAttribute() == TR_ENEMYENDTILE)
	{
		AStarTile* curr = minTile->GetParentTile();

		POINT listPos = currPos;

		//한칸만 이동 엔드 지점까지 가는 경우가 없음으로;;; 생각해보기;
		/*if (curr->GetParentTile() == nullptr)
		{
			listPos.x = (minTile->GetIdX() - posIndex.x);
			listPos.y =(minTile->GetIdY() - posIndex.y);
			isOneTile = true;
			pathList.push_back(listPos);
		}*/
		
		while (curr->GetParentTile() != nullptr)
		{
			listPos.x = curr->GetIdX() - curr->GetParentTile()->GetIdX();
			listPos.y = curr->GetIdY() - curr->GetParentTile()->GetIdY();
			pathList.push_back(listPos);
			curr = curr->GetParentTile();
		}

		openList.clear();
		closeList.clear();
		isOneTile = false;
		hasPath = true;
		playAni->Start();
		tiletX = posIndex.x;
		tiletY = posIndex.y;
		return;
	}
	// 지나온 타일을 클로즈리스트에 추가한다.
	closeList.push_back(minTile);
	// 오픈리스트에서 제거한다.
	for (vector<AStarTile*>::iterator it = openList.begin(); it != openList.end(); it++)
	{
		if ((*it) == minTile)
		{
			openList.erase(it);
			break;
		}
	}
	// 제일 가까운 타일을 기준으로 알고리즘을 반복한다.
	if (currTile != minTile)
	{
		currTile = minTile;
	}

	AstarPath(currTile);
}

void Enemy::AddOpenList(AStarTile * currentTile)
{
	int startX = currentTile->GetIdX() - 1;
	int startY = currentTile->GetIdY() - 1;
	int sideX, sideY;
	bool isAdd = false;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 1 && j == 2) || (i == 2 && j == 1))) continue;
			if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 1 && j == 2) || (i == 2 && j == 1))
			{
				sideX = startX + j;
				sideY = startY + i;

				// 타일맵 영역을 벗어났을 때
				if (sideX < 0 || sideX >= ASTAR_TILE_NUM_X ||
					sideY < 0 || sideY >= ASTAR_TILE_NUM_Y)
				{
					continue;
				}

				AStarTile* tile = tiles[(sideY * ASTAR_TILE_NUM_X) + sideX];

				// 오픈 리스트에 넣지 않는 경우
				/*
					start, wall, openList,이미 closeList에 들어있는 경우
				*/

				if (tile->GetAttribute() == TR_BLOCK || tile->GetAttribute() == TR_WATER || tile->GetAttribute() == TR_CLIFF || tile->GetAttribute() == TR_ENEMYSTARTTILE) continue;

				// 이미 오픈리스트에 있을 때 예외처리
				bool isExist = false;
				for (vector<AStarTile*>::iterator it = openList.begin(); it != openList.end(); it++)
				{
					if ((*it) == tile)
					{
						isExist = true;
						break;
					}
				}

				if (isExist) continue;

				// 클로즈리스트에 있을 때 예외처리
				isExist = false;
				for (vector<AStarTile*>::iterator it = closeList.begin(); it != closeList.end(); it++)
				{
					if ((*it) == tile)
					{
						isExist = true;
						break;
					}
				}

				if (isExist) continue;


				openList.push_back(tile);
				tile->SetParentTile(currentTile);
				isAdd = true;
			}

		}
	}


}

void Enemy::MovePathCheck()
{
	if (pathList.size() >= 0 && (isLinkArea))
	{

		tiletX1 = posIndex.x + pathList.back().x;
		tiletY1 = posIndex.y + pathList.back().y;

		//시작 지점에서 왼쪽 이동

		if (tiletX > tiletX1&& enemystate != LEFT)
		{
			playAni = moveAni;
			enemystate = LEFT;
			if (typeNum == 2) { playAni->SetPlayFrame(7, 13, true, true); }
			else playAni->SetPlayFrame(4, 7, true, true);
			playAni->Start();

		}
		else if (tiletX < tiletX1&& enemystate != RIGHT)
		{
			playAni = moveAni;
			enemystate = RIGHT;
			if (typeNum == 2) { playAni->SetPlayFrame(14, 20, true, true); }
			else playAni->SetPlayFrame(8, 11, true, true);
			playAni->Start();

		}
		else if (tiletY > tiletY1 && enemystate != TOP)
		{
			playAni = moveAni;
			enemystate = TOP;
			if (typeNum == 2) { playAni->SetPlayFrame(0, 6, true, true); }
			else playAni->SetPlayFrame(0, 3, true, true);
			playAni->Start();

		}
		else if (tiletY < tiletY1&& enemystate != BOTTOM)
		{
			playAni = moveAni;
			enemystate = BOTTOM;
			if (typeNum == 2) { playAni->SetPlayFrame(21, 27, true, true); }
			else playAni->SetPlayFrame(12, 15, true, true);
			playAni->Start();

		}


		//변경된 위치의 타일 주소 처리 
		fieldTileInfo[indexNum].enemy = nullptr;
		if (tiletX != tiletX1)
		{
			if (indexNum%FIELDTILE_X_2 < (FIELDTILE_X_2 - 1))
			{
				indexNum += pathList.back().x;
			}
		}
		if (tiletY != tiletY1)
		{
			if (indexNum / FIELDTILE_X_2 < 183)
			{
				indexNum += (pathList.back().y * FIELDTILE_X_2);
			}
		}
		fieldTileInfo[indexNum].enemy = this;
		tiletX = tiletX1;
		tiletY = tiletY1;
		posIndex.x = indexNum % FIELDTILE_X_2 - tilePosX;;
		posIndex.y = indexNum / FIELDTILE_X_2 - tilePosY;;
	
		pos.x = posIndex.x * 64 + movePos.x;
		pos.y = posIndex.y * 64 + movePos.y;

		pathList.pop_back();
	}
	else
	{
		if (iswaitTime)
		{
			iswaitTime = false;
			playAni = moveAni;
			enemystate = BOTTOM;
			if (typeNum == 2) { playAni->SetPlayFrame(21, 27, true, true); }
			else playAni->SetPlayFrame(12, 15, true, true);
			//playAni->Start();

		}

	}

	return;
}

void Enemy::AttMotion()
{
	if (isAttMode)
	{

		if (pos.x > link->GetPos().x&&pos.y == link->GetPos().y&& enemystate != LEFT)
		{
			playAni = attAni;
			enemystate = LEFT;
			if (typeNum == 2){ playAni->SetPlayFrame(6, 11, true, true); }
			else playAni->SetPlayFrame(4, 7, false, true);
			playAni->Start();

		}
		else if (pos.x < link->GetPos().x&&pos.y == link->GetPos().y&& enemystate != RIGHT)
		{
			playAni = attAni;
			enemystate = RIGHT;
			if (typeNum == 2 ) { playAni->SetPlayFrame(12, 17, true, true); }
			else playAni->SetPlayFrame(8, 11, false, true);
			playAni->Start();

		}
		else if (pos.y > link->GetPos().y && pos.x == link->GetPos().x&& enemystate != TOP)
		{ 
			playAni = attAni;
			enemystate = TOP;

			if (typeNum == 2 ) { playAni->SetPlayFrame(0, 5, true, true); }
			else playAni->SetPlayFrame(0, 3, false, true);
			playAni->Start();

		}
		else if (pos.y < link->GetPos().y&& pos.x == link->GetPos().x&& enemystate != BOTTOM)
		{
			playAni = attAni;
			enemystate = BOTTOM;
			if (typeNum == 2 ) { playAni->SetPlayFrame(18, 23, true, true); }
			else playAni->SetPlayFrame(12, 15, false, true);
			playAni->Start();

		}

		if (pos.y == link->GetPos().y&& pos.x == link->GetPos().x)
		{
			playAni->Stop();
		}
	}

}

void Enemy::AttCheck()
{
	attTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (!hasHitting && !(link->GetHasAttacked()))
	{
		if (posIndex.x == link->GetLinkIndexPos().x&& posIndex.y == link->GetLinkIndexPos().y)
		{
			if (!link->GetIsDef()|| !link->GetIsRollingMove())
			{
				link->SetHp(link->GetHp() - 1);
				link->SetHasAttacked(true);
			}
			hasHitting = true;
		}
		else if (isAttMode)
		{
			if (posIndex.x - 1 == link->GetLinkIndexPos().x && posIndex.y == link->GetLinkIndexPos().y&& enemystate == LEFT)
			{
				if (!link->GetIsDef())
				{
					link->SetHp(link->GetHp() - 1);
					link->SetHasAttacked(true);
				}
				hasHitting = true;
			}
			else if (posIndex.x + 1 == link->GetLinkIndexPos().x && posIndex.y == link->GetLinkIndexPos().y&& enemystate == RIGHT)
			{
				if (!link->GetIsDef())
				{
					link->SetHp(link->GetHp() - 1);
					link->SetHasAttacked(true);
				}
				hasHitting = true;
			}
			else if (posIndex.x == link->GetLinkIndexPos().x && posIndex.y - 1 == link->GetLinkIndexPos().y&& enemystate == TOP)
			{
				if (!link->GetIsDef())
				{
					link->SetHp(link->GetHp() - 1);
					link->SetHasAttacked(true);
				}
				hasHitting = true;
			}
			else if (posIndex.x == link->GetLinkIndexPos().x && posIndex.y + 1 == link->GetLinkIndexPos().y&& enemystate == BOTTOM)
			{
				if (!link->GetIsDef())
				{
					link->SetHp(link->GetHp() - 1);
					link->SetHasAttacked(true);
				}
				hasHitting = true;
			}
		}
	}
	else if (hasHitting == true)
	{
		if (attTime >= 1.2f)
		{
			hasHitting = false;
			attTime = 0.0f;
		}

	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
