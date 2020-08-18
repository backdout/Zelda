#pragma once
#include "GameNode.h"
#include"pch.h"

class ButtonFunc : public GameNode
{
private:
	int tileframeX, tileframeY;
	int sampletileframeX, sampletileframeY;

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

	// 주로 스택틱 함수나 전역 함수로 사용 ; ( 번잡 스러워서;
	static void ChangeScene() { SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1"); };
	
	void ChangeScene1() { SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1"); };
	



	void ChangeScene2(const char* filename, const char* filename2) { SceneManager::GetSingleton()->ChangeScene(filename, filename2); };
	
	void SetMapBt();
	
	void MapLeft();
	void MapRight();
	void MapUp();
	void MapDown();

	void SampleMapLeft();
	void SampleMapRight();
	void SampleMapUp();
	void SampleMapDown();

	void FieldBt();
	void CastleBt();
	void DungeonBt();
	void TerrainBt();
	void NoneBt();
	void BlockBt();
	void WaterBt();
	void CliffBt();
	void ObjBt();

	int GetTileframeX() { return tileframeX; };
	int GetTileframeY() { return tileframeY; };
	int GetSampletileframeX() { return sampletileframeX; };
	int GetSampletileframeY() { return sampletileframeY;};

	bool GetIsFieldSelect() { return isFieldSelect; };
	bool GetIsCastleSelect() { return isCastleSelect; };
	bool GetIsDungeonSelect() { return isDungeonSelect; };
	bool GetIsTerraninSelect() { return isTerraninSelect; };
	bool GetIisNoneSelect() { return isNoneSelect;};
	bool GetIsBlockSelect() { return isBlockSelect; };
	bool GetIsWaterSelect() { return isWaterSelect; };
	bool GetIsCliffSelect() { return isCliffSelect; };
	bool GetIsObjSelect() { return isObjSelect;}





	ButtonFunc() {};
	~ButtonFunc() {};
};


