#include <DxLib.h>
#include "GameTask.h"
#include "editCursor.h"



editCursor::editCursor(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 _chipOffset)
	:Obj(_keydata, _keydataOld, _chipOffset)
{
	nowID = BF_CHIP_WATER1;	// èâä˙ÇÃÃﬁ€Ø∏
	keyGetRng = editKeyGetDefRng;
	inputFlam = editKeyGetDefRng;
	pos = ((lpMapCtl.GetViewAreaSize() / 2) * lpMapCtl.GetChipSize());
}

editCursor::~editCursor()
{
}

bool editCursor::Update()
{
	move();
	SetChipID();
	return false;
}

void editCursor::Draw()
{
	Obj::Draw(nowID);
}

bool editCursor::SetChipID()
{
	if (keydata[KEY_INPUT_SPACE])
	{
		SET_MAP_ID(pos, nowID);
	}
	if (keydata[KEY_INPUT_D])
	{
		SET_MAP_ID(pos, BF_CHIP_BLANK);
	}
	return true;
}

void editCursor::move()
{
	int chipSize = lpMapCtl.GetChipSize();
	if (keydata[KEY_INPUT_A] && !keydataOld[KEY_INPUT_A])
	{
		if (nowID <= BF_CHIP_BLANK)
		{
			nowID = LAST_EDIT_CHIP;
		}
		else
		{
			nowID = (CHIP_TYPE)(nowID - 1);
		}
	}
	if (keydata[KEY_INPUT_S] && !keydataOld[KEY_INPUT_S])
	{
		if (nowID >= LAST_EDIT_CHIP)
		{
			nowID = BF_CHIP_BLANK;
		}
		else
		{
			nowID = (CHIP_TYPE)(nowID + 1);
		}
	}
	VECTOR2 GameArea = lpMapCtl.GetViewAreaSize();
	VECTOR2 tmpPos = pos;

	if ((keydata[KEY_INPUT_NUMPAD8]) && !keydataOld[KEY_INPUT_NUMPAD8]
		|| (keydata[KEY_INPUT_UP]) && !keydataOld[KEY_INPUT_UP])
	{
		pos.y -= speed;
	}
	if (keydata[KEY_INPUT_NUMPAD2] && !keydataOld[KEY_INPUT_NUMPAD2]
		|| (keydata[KEY_INPUT_DOWN]) && !keydataOld[KEY_INPUT_DOWN])
	{
		pos.y += speed;
	}
	if (keydata[KEY_INPUT_NUMPAD4] && !keydataOld[KEY_INPUT_NUMPAD4]
		|| (keydata[KEY_INPUT_LEFT]) && !keydataOld[KEY_INPUT_LEFT])
	{
		pos.x -= speed;
	}
	if (keydata[KEY_INPUT_NUMPAD6] && !keydataOld[KEY_INPUT_NUMPAD6]
		|| (keydata[KEY_INPUT_RIGHT]) && !keydataOld[KEY_INPUT_RIGHT])
	{
		pos.x += speed;
	}

}
