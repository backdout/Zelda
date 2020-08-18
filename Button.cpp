#include "Button.h"
#include "Image.h"
#include "pch.h"
#include "TitleScene.h"
#include "ButtonFunc.h"
#include "Construction.h"


HRESULT Button::Init(const char* imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	state = BUTTON_STATE::NONE;
	pos.x = posX;
	pos.y = posY;
	this->btnDownFramePoint = btnDownFramePoint;
	this->btnUpFramePoint = btnUpFramePoint;
	openObj = false;
	isSaveBt = false;
	isLoadBt = false;
	tile = nullptr;
	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
	if (image == nullptr)
		return E_FAIL;

	rc = GetRect(pos.x- image->GetFrameWidth()/2, pos.y - image->GetFrameHeight()/2,
		image->GetFrameWidth()*2.1, image->GetFrameHeight()*2.1);
	isDirBt = false;
	return S_OK;
}
HRESULT Button::Init(const char* imageName, int posX, int posY, int frameX ,int frameY,POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	state = BUTTON_STATE::NONE;
	pos.x = posX;
	pos.y = posY;
	this->btnDownFramePoint = btnDownFramePoint;
	this->btnUpFramePoint = btnUpFramePoint;
	openObj = false;
	isSaveBt = false;
	isLoadBt = false;
	tile = nullptr;
	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
	if (image == nullptr)
		return E_FAIL;

	rc = GetRectToCenter(pos.x, pos.y,
		image->GetFrameWidth()*2.1, image->GetFrameHeight()*2.1);
	isDirBt = false;
	return S_OK;
}

//HRESULT Button::Init(const char* imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint, void (ButtonFunk::*ButtonFunc1)(const char*), ButtonFunk* btnfunc)
//{
//	state = BUTTON_STATE::NONE;
//	pos.x = posX;
//	pos.y = posY;
//	this->btnDownFramePoint = btnDownFramePoint;
//	this->btnUpFramePoint = btnUpFramePoint;
//
//
//	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
//
//	rc = GetRectToCenter(pos.x, pos.y,
//		image->GetFrameWidth(), image->GetFrameHeight());
//	this->btnfunc = btnfunc;
//	this->ButtonFunc = nullptr;
//	this->ButtonFunc1 = ButtonFunc1;
//	return S_OK;
//}
//
//HRESULT Button::Init(const char * imageName, int posX, int posY, POINT btnDownFramePoint, POINT btnUpFramePoint, void(ButtonFunk::* ButtonFun1)(const char*), ButtonFunk * btnfunc, const char * filename)
//{
//	state = BUTTON_STATE::NONE;
//	pos.x = posX;
//	pos.y = posY;
//	this->btnDownFramePoint = btnDownFramePoint;
//	this->btnUpFramePoint = btnUpFramePoint;
//
//
//	image = ImageManager::GetSingleton()->FindImage(imageName); // 다른 곳에서 add 처리 
//
//	rc = GetRectToCenter(pos.x, pos.y,
//		image->GetFrameWidth(), image->GetFrameHeight());
//	this->btnfunc = btnfunc;
//	this->ButtonFunc = nullptr;
//	this->ButtonFunc1 = ButtonFunc1;
//	this->sceneName = filename;
//	return S_OK;
//}


void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse)) //Point가 Rect안에 들어가있으면 True를 반환해서 아래가 실행된다.
	{
		if (!isDirBt)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				state = BUTTON_STATE::DOWN;
				stateNum = 2;

				if (btnfunc&&ButtonFunc1)
				{
					(btnfunc->*ButtonFunc1)();
				}
				else if (btnfunc&&ButtonFunc2)
				{
					(btnfunc->*ButtonFunc2)(args->sceneName, args->loadingName);
				}

			}
		}
		else  if (isDirBt)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				state = BUTTON_STATE::DOWN;
				stateNum = 2;

				if (btnfunc&&ButtonFunc1)
				{
					(btnfunc->*ButtonFunc1)();
				}
				else if (btnfunc&&ButtonFunc2)
				{
					(btnfunc->*ButtonFunc2)(args->sceneName, args->loadingName);
				}
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && state == BUTTON_STATE::DOWN)
		{
			state = BUTTON_STATE::UP;
			stateNum = 1;
			

			/*if (!(btnfunc)&&tile)
			{
				
				if (isSaveBt)
				{
					tile->Save();
				}
				if (isLoadBt)
				{
					tile->Load();
				}

				if (openObj)
				{
					btnUpFramePoint.y = 1;
					openObj = false;
				}
				else if (!openObj && !isLoadBt & !isSaveBt)
				{
					btnUpFramePoint.y = 0;
					openObj = true;
				}*/
			//}
			
		}
	}
	else
	{
		state = BUTTON_STATE::NONE;
		stateNum = 0;
	}

}

void Button::Render(HDC hdc)
{

	switch (stateNum)
	{
	case BUTTON_STATE::DOWN:
		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnDownFramePoint.x, btnDownFramePoint.y,2.1);
		break;

	case BUTTON_STATE::NONE:
	case BUTTON_STATE::UP:

		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnUpFramePoint.x, btnUpFramePoint.y,2.1);

		break;
	}
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//RenderRectToCenter(hdc, pos.x, pos.y, image->GetFrameWidth(), image->GetFrameHeight());
}

void Button::ChangeScene()
{
	SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1");
}

void Button::CloseBox()
{
}

Button::Button()
{
}

Button::~Button()
{
}
