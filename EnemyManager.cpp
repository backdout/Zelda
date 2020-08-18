#include "EnemyManager.h"
#include "Enemy.h"
#include "Link.h"


HRESULT EnemyManager::Init()
{
	SetEnemy1IndexPos();
	isSetting = false;
	dieCount = 0;
	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		SAFE_DELETE((*itEnemys));
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	int die = 0;
	vecIndeX = 0;
	/*if (!isSetting)
	{
		isSetting = true;
		for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
		{
			(*itEnemys)->SetLink(link);
		}
	}*/
	for (auto itIndex1 : enemy1)
	{
		//if (enemy1.find(itIndex1)->second->GetActEnemy())continue;

		posIndex.x = (itIndex1.first % FIELDTILE_X_2) - tilePosX;
		posIndex.y = (itIndex1.first / FIELDTILE_X_2) - tilePosY;
		if (posIndex.x >= 0 && posIndex.x < 18 && posIndex.y >= 0 && posIndex.y < 15)
		{
			//enemy1IndexPos.erase(itIndex1);
			if (itIndex1.second->GetActEnemy())continue;

			itIndex1.second->SetFieldTileInfo(fieldTileInfo);
			itIndex1.second->Init(itIndex1.first);
			itIndex1.second->SetActEnemy(true);
			itIndex1.second->SetLink(link);
			vecEnemys.push_back(itIndex1.second);
			enemy1.erase(itIndex1.first);
			break;
		}
		/*else
		{
			enemy1.find(itIndex1)->second->SetActEnemy(false);
		}*/
		vecIndeX++;
	}
	vecIndeX = 0;

	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		if ((*itEnemys) != nullptr)
		{
			(*itEnemys)->SetTilePosX(tilePosX);
			(*itEnemys)->SetTilePosY(tilePosY);
			(*itEnemys)->SetTileInfo(tileInfo);
			(*itEnemys)->SetMovePos(movePos);
			(*itEnemys)->Update();
			if (!((*itEnemys)->GetActEnemy())|| (*itEnemys)->GetIsDie()) // 비활성화 된 몹은 반환
			{

				if (enemy1.find((*itEnemys)->GetIndexNum()) == enemy1.end())// 맵에 없는 경우만 삽입 
				{
					// 맵에 넣고, 벡터에서 제거
					enemy1.insert(make_pair((*itEnemys)->GetIndexNum(), (*itEnemys)));
					vecEnemys.erase(vecEnemys.begin() + vecIndeX);
					break;
				}

				
			}
		
		}
		vecIndeX++;
	}

	


}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		if ((*itEnemys) != nullptr)
		{
			(*itEnemys)->Render(hdc);
		}
	}
}

void EnemyManager::SetEnemy1IndexPos()
{
	//enemy1.insert()
	if(LinkManager::GetSingleton()->GetHasNewStared()==false)
	{ 
		if (!isLoad)
		{
			if (enemy1.size() >= 1)
			{
				enemy1.clear();
			}
			ifstream fin;
			fin.open("enemy1Info.txt");
			int index;
			int size;
			fin >> size;
		
			//vecEnemys.resize(size);
			for (int i = 0; i <= size; i++)
			{
				Enemy* enemy = new Enemy();
				enemy->SetTypeNum(0);
				fin >> index;
				if (index < 100)
				{
					size = index;
					break;
				}
				//enemy1IndexPos.push_back(index);
				enemy1.insert(make_pair(index, enemy));
			}
			for (int i = 0; i <= size; i++)
			{
				Enemy* enemy = new Enemy();
				enemy->SetTypeNum(1);
				fin >> index;
				if (index < 100)
				{
					size = index;
					break;
				}
				//enemy1IndexPos.push_back(index);
				enemy1.insert(make_pair(index, enemy));
			}
			for (int i = 0; i < size; i++)
			{
				Enemy* enemy = new Enemy();
				enemy->SetTypeNum(2);
				fin >> index;
				if (index < 100)
				{
					size = index;
					break;
				}
				//enemy1IndexPos.push_back(index);
				enemy1.insert(make_pair(index, enemy));
			}
		}
		else
		{
			for (int i = 0; i <= 50; i++)
			{

				if (enemyInfo[i].index == NULL) continue;
				else
				{
					Enemy* enemy = new Enemy();
					enemy->SetTypeNum(enemyInfo[i].type);
					enemy->SetIsDie(enemyInfo[i].isDie);
					//enemy1IndexPos.push_back(index);
					enemy1.insert(make_pair(enemyInfo[i].index, enemy));
				}
			}

		}
	}
	if (LinkManager::GetSingleton()->GetIsLoadField()==false&& LinkManager::GetSingleton()->GetHasNewStared() == true&& LinkManager::GetSingleton()->GetIsField()==false)
	{
		for (int i = 0; i <= 50; i++)
		{

			if (enemyInfo[i].index == NULL) continue;
			else
			{
				Enemy* enemy = new Enemy();
				enemy->SetTypeNum(enemyInfo[i].type);
				enemy->SetIsDie(enemyInfo[i].isDie);
				//enemy1IndexPos.push_back(index);
				enemy1.insert(make_pair(enemyInfo[i].index, enemy));
			}
		}
		LinkManager::GetSingleton()->SetIsLoadField(true);
	}

}

void EnemyManager::AddEnemy(float posX, float posY)
{
	Enemy* enemy = new Enemy();
	enemy->SetLink(link);
	//1번 위치 0,0 2번 6,0 3번 12,0;
//	enemy->Init(posX, posY);
	enemy->SetLink(link);
	//enemy->SetTileInfo(tileInfo);
	vecEnemys.push_back(enemy);
}

void EnemyManager::Save()
{

	//활성화되어 벡터에 있는 애들을 맵에다시 넣기 
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		if ((*itEnemys) != nullptr)
		{
			if (saveEnemy.find((*itEnemys)->GetIndexNum()) == saveEnemy.end())// 맵에 없는 경우만 삽입 
			{
				// 맵에 넣고, 벡xj에서 제거
				saveEnemy.insert(make_pair((*itEnemys)->GetIndexNum(), (*itEnemys)));
				break;
			}

			
		}
	}

	for (auto itenmy : enemy1)
	{
		saveEnemy.insert(make_pair(itenmy.first, itenmy.second));
	}
	int Index = 0;
	for (auto itenmy : saveEnemy)
	{
		enemyInfo[Index].index = itenmy.first;
		enemyInfo[Index].type = itenmy.second->GetTypeNum();
		enemyInfo[Index].isDie = itenmy.second->GetIsDie();
		Index += 1;
		
	}

	//맵 타입으로 저장 
	DWORD writtenByte;
	HANDLE hFile = CreateFile("Save/EnemyInfo", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, enemyInfo, sizeof(ENEMY_INFO)*50, &writtenByte, NULL);
	CloseHandle(hFile);


	//map<int, Enemy*> enemy1;

}

void EnemyManager::Load()
{
	//for( )
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		SAFE_DELETE((*itEnemys));
	}
	vecEnemys.clear();

	for (auto itenmy : enemy1)
	{

		//itenmy.second->Release();
		//SAFE_DELETE(itenmy.second);
	}
	enemy1.clear();

	for (auto itenmy : saveEnemy)
	{
		/*if (itenmy.second != nullptr)
		{
			itenmy.second->Release();
			SAFE_DELETE(itenmy.second);
		}*/
	}
	saveEnemy.clear();
	for (int i = 0; i < 50; i++)
	{
		enemyInfo[i].index = NULL;
		enemyInfo[i].isDie = NULL;
		enemyInfo[i].type = NULL;
	}

	DWORD readByte;
	HANDLE hFile = CreateFile("Save/EnemyInfo", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, enemyInfo, sizeof(ENEMY_INFO)*50, &readByte, NULL);
	CloseHandle(hFile);
	isLoad = true;
	SetEnemy1IndexPos();

}

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
