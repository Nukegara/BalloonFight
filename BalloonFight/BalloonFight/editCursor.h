#pragma once
#include "Obj.h"
#include "mapControl.h"

constexpr int editKeyGetDefRng = 30;	// ·°ˆ—‚ÌŠÔŠu

class editCursor : 
	public Obj
{
public:
	editCursor(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 _chipOffset);
	~editCursor();
	bool Update();
	void Draw();
	char keyData[256];
	char keyDataOld[256];

private:
	bool SetChipID();
	void move();
	CHIP_TYPE nowID;
	unsigned int keyGetRng;	// Ÿ‚Ì·°ˆ—‚Ü‚Å‚ÌŠÔŠu
	unsigned int inputFlam;	// ‘O‰ñ‚ÌˆÚ“®‚©‚ç‚ÌÌÚ°Ñ
};

