#pragma once
#include "DxLib.h"
#include <memory>
#include <list>
#include "Obj.h"

constexpr int ScreenSizeX = 16 * 50;	// âÊñ â°ª≤Ωﬁ
constexpr int ScreenSizeY = 16 * 37;	// âÊñ ècª≤Ωﬁ
typedef std::shared_ptr<Obj> obj_ptr;
typedef std::list<obj_ptr> obj_List;
#define lpGameTask GameTask::GetInstance()

class Field;
enum GMODE
{
	GMODE_INIT,
	GMODE_TITLE,
	GMODE_MAIN,
	GMODE_OVER,
	GMODE_CLEAR,
	GMODE_EDIT_INIT,
	GMODE_EDIT_MAIN,
	GMODE_MAX
};

class GameTask
{
public:
	int SysInit();		// ºΩ√—ånèâä˙âª
	static GameTask& GetInstance()
	{
		static GameTask getInstance;
		return getInstance;
	}
	int Update();
	bool CheckEditMode();

	GameTask();
	GameTask(const GameTask&) {}
	GameTask operator = (const GameTask&) {}
	~GameTask();
	std::list<obj_ptr>::iterator addObjList(obj_ptr && objptr);

	char keyData[256];
	char keyDataOld[256];

	const VECTOR2 GetAreaOffset();
	const VECTOR2 &GetDrawOffset();

	void ChangeGameMode(GMODE);

	VECTOR pos;
	VECTOR norm;
	GMODE gameMode;
private:
	int GameInit();		// πﬁ∞—ånèâä˙âª
	int GameTitle();
	int GameMain();
	int GameOver();
	int GameClear();
	int GameDestroy();
	int EditInit();
	int EditMain();
	int EditDestroy();
	int SysDestroy();

	static GameTask *s_Instance;
	int (GameTask::*GtskPtr)(void);
	int cnt;
	obj_List objList;
};
