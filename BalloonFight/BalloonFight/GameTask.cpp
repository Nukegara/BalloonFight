#pragma once
#include <memory>
#include <list>
#include "Obj.h"
#include "GameTask.h"
#include "ImageMng.h"
#include "editCursor.h"
//#include "KeyMng.h"

GameTask *GameTask::s_Instance = nullptr;

typedef std::shared_ptr<Obj> obj_ptr;
typedef std::list<obj_ptr> obj_List;
#define lpGameTask GameTask::GetInstance()

std::list<obj_ptr>::iterator GameTask::addObjList(obj_ptr && objptr)
{
	objList.push_back(objptr);
	auto itr = objList.end();
	itr--;
	return itr;
}

GameTask::GameTask()
{
	GtskPtr = &GameTask::SysInit;
	//SysInit();

	//gameMode = GMODE_INIT;
}

GameTask::~GameTask()
{
}

int GameTask::GameInit()
{
	DrawString(10, 10, "Init", 0xffffff, true);
	objList.clear();
	lpMapCtl.MapLoad();
	GtskPtr = &GameTask::GameMain;
	return true;
}

int GameTask::GameTitle()
{
	DrawString(10, 10, "Title", 0xffffff, true);


	return 0;
}

int GameTask::GameMain()
{
	DrawString(10, 10, "Main", 0xffffff, true);
	ClsDrawScreen();

	lpMapCtl.MapDraw();
	for (auto itr = objList.begin(); itr != objList.end(); ++itr)
	{
		(*itr)->Update();
	}
	for (auto itr = objList.begin(); itr != objList.end(); ++itr)
	{
		(*itr)->Draw();
	}
	ScreenFlip();
	return true;
}

int GameTask::GameOver()
{
	//cnt++;
	DrawString(10, 10, "GameOver", 0xffffff, true);
	return 0;
}

int GameTask::GameClear()
{
	return 0;
}

int GameTask::GameDestroy()
{
	return 0;
}

bool GameTask::CheckEditMode()
{
	if (GtskPtr == &GameTask::EditMain)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int GameTask::EditInit()
{
	DrawString(10, 10, "EditInit", 0xffffff, true);

	objList.clear();

	objList.push_back(std::make_shared < editCursor >(keyData, keyDataOld, VECTOR2(0, 0)));
	auto itr = objList.end();	// ���ۂ̒��g�͋�
	itr--;

	(*itr)->Init("image/stage3.png", { GET_CHIP_SIZE, GET_CHIP_SIZE }, { 8, 3 }, { 1, 0 }, GET_CHIP_SIZE);
	GtskPtr = &GameTask::EditMain;
	return true;
}

int GameTask::EditMain()
{
	ClsDrawScreen();

	lpMapCtl.MapDraw();
	VECTOR2 viewArea = lpMapCtl.GetViewAreaSize();
	int chipSize = lpMapCtl.GetChipSize();
	VECTOR2 tmpPos;

	for (auto itr = objList.begin(); itr != objList.end(); ++itr)
	{
		(*itr)->Update();
	}

	for (auto itr = objList.begin(); itr != objList.end(); ++itr)
	{
		(*itr)->Draw();
	}

	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, 0);
	if (lpGameTask.CheckEditMode())
	{
		for (int x = /*chipSize * 2*/ 0; x < ScreenSizeX/* - chipSize*/; x += chipSize)
		{
			DrawLine(x, /*chipSize*/ 0, x, ScreenSizeY/* - ScreenSizeY % chipSize + 1*/, 0xf0f0f0, true);
		}

		for (int y = /*chipSize*/ 0; y < ScreenSizeX/* - ScreenSizeY % chipSize*/; y += chipSize)
		{
			DrawLine(/*chipSize * 2*/ 0, y, ScreenSizeX/* - chipSize * 2*/, y, 0xf0f0f0, true);
		}
	}
	ScreenFlip();
	return true;
}

const VECTOR2 GameTask::GetAreaOffset()
{
	return VECTOR2(lpMapCtl.GetChipSize() * 2, lpMapCtl.GetChipSize());
}

const VECTOR2 & GameTask::GetDrawOffset()
{
	return -(lpMapCtl.GetViewAreaSize() / 2) * lpMapCtl.GetChipSize();
}

//void GameTask::ChangeGameMode(GMODE gmode)
//{
//	gameMode = gmode;
//}

int GameTask::SysInit()
{
	SetWindowText("1701322_���� ��R��");
	SetGraphMode(ScreenSizeX, ScreenSizeY, 16);		// ��`�������ނ�16bit�װ�ŕ\�������
	ChangeWindowMode(true);								// ture:windows	false:�ٽ�ذ�
	
	// Dxײ���؂̏�����
	if (DxLib_Init() == -1)								// Dxײ���؂̏�����
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	ImageMng::Create();
	GtskPtr = &GameTask::EditInit;

	// �w�i�F�̕ύX
	//SetBackgroundColor(255, 255, 255);

	return true;
}

int GameTask::Update()
{
	int rtn_id;
	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
	if ((keyData[KEY_INPUT_F5]) && (!keyDataOld[KEY_INPUT_F5]))
	{
		if (GtskPtr == &GameTask::EditMain)
		{
			GtskPtr = &GameTask::GameInit;
		}
		else if (GtskPtr == &GameTask::GameMain)
		{
			GtskPtr = &GameTask::EditInit;
		}
		else
		{
			// ��O�̏ꍇ�͉������Ȃ�
		}
	}
	if (GtskPtr == &GameTask::EditMain)
	{
		if ((keyData[KEY_INPUT_F1]) && (keyDataOld[KEY_INPUT_F1]))
		{
			if (MessageBox(GetMainWindowHandle(), "���e����", "��ި�ľ��ފm�F",
				MB_YESNO + MB_ICONQUESTION) == IDYES)
			{
				lpMapCtl.MapSave();
			}
		}
		if ((keyData[KEY_INPUT_F2]) && (!keyDataOld[KEY_INPUT_F2]))
		{
			if (MessageBox(GetMainWindowHandle(), "���e��۰��", "��ި��۰�ފm�F",
				MB_YESNO + MB_ICONQUESTION) == IDYES)
			{
				lpMapCtl.MapLoad();
			}
		}
	}
	rtn_id = (this->*GtskPtr)();

	return rtn_id;
}

int GameTask::EditDestroy()
{
	return true;
}

int GameTask::SysDestroy()
{
	ImageMng::Destroy();
	return 0;
}

