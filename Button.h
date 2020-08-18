#pragma once
#include "GameNode.h"
#include "macroFunction.h"
#include "pch.h"
/*
 �Լ� ������ -> �Լ��� �ּҸ� ��� ���� 
 ������ -> ������ �ּҸ� ��� ����
 int a=10; 
 int* pA= &a;


 int sum(int a, int b);
 int (*caculPointer) (int a, int b);// �����̱� ���� �ε� ó�� Ȱ�� �Ұ�; 


 caculPointer= sum;

 void Funk(void); 

 void (*FunkPointer)(void);  �Լ� ������ ������ ���� �ϴ� ����;

 FunkPointer= Funk;// �Լ������Ϳ� �Լ� �ּҸ� ����; 




 FunkPointer(); // ==Funk();



 //void makeRect(


 */


enum BUTTON_STATE
{
	NONE,
	UP,
	DOWN
};
class Image;
class Construction;
class ButtonFunc;
class Button :public GameNode
{

private:

	BUTTON_STATE state;
	Image* image;
	RECT rc;
	//int id;
	Construction* tile;
	Construction* tileSave;
	POINT btnDownFramePoint;
	POINT btnUpFramePoint;

	
	ButtonFunc* btnfunc;
	
	//const char* sceneName;
	ARG_INFO* args;

	// ��ư ������ ���� �Լ� ������

	void(*ButtonFunc0)(void);

	void(ButtonFunc::*ButtonFunc1)(void);
	void(ButtonFunc::*ButtonFunc2)(const char*, const char*);

	bool isLoadBt;
	bool isSaveBt;
	bool openObj;
	int stateNum;
	bool isDirBt;
	//bool isLoadBt;

public:
	
	HRESULT Init(const char* imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint );
	HRESULT Init(const char* imageName, int posX, int posY, int frameX, int frameY, POINT btnDownFramePoint, POINT btnUpFramePoint);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTile(Construction* _tile) { tile = _tile; }
	void SetTileSave(Construction* _tileSave) { tileSave = _tileSave; }
	void SetButtonFunc(ButtonFunc* bf,void(ButtonFunc::*ButtonFunc1)(void) = nullptr, void (ButtonFunc::*ButtonFunc2)(const char*, const char*) = nullptr, ARG_INFO* args = NULL)
	{
		this->btnfunc = bf;
		//this->ButtonFunc = nullptr;
		this->ButtonFunc1 = ButtonFunc1;
		this->ButtonFunc2 = ButtonFunc2;
		this->args = args;


	}

	void SetOpenObj(bool _openObj) { openObj = _openObj; }
	void SetIsSaveBt(bool _isSaveBt) { isSaveBt = _isSaveBt; }
	void SetIsLoadBt(bool _isLoadBt) { isLoadBt = _isLoadBt; }
	bool GetOpenObj() {return openObj; }
	void SetStateNum(int _stateNum) { stateNum = _stateNum; }

	void SetIsDirBt(bool _isDirBt) { isDirBt = _isDirBt; }
	RECT GetRc() { return rc; }

	void ChangeScene();
	void CloseBox();

	Button();
	virtual~Button();

};

