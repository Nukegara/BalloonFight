#include "DxLib.h"
#include "Player.h"
#include "mapControl.h"
#include "GameTask.h"

bool moveLR = false;
int animAdd = 0;


Player::Player(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 _chipOffset)
	:Obj(_keydata, _keydataOld, _chipOffset)
{
	dir = DIR_L;
	velocityX = 0;
	velocityY = 0;
}


Player::~Player()
{
}

bool Player::Update()
{
	SetMove();
	return false;
}

bool Player::initAnim()
{
	addAnim("立ち2", 0, 0, 3, 8);
	addAnim("歩き2", 3, 0, 4, 4);
	addAnim("扇ぐ2", 7, 0, 4, 6);
	addAnim("落下2", 11, 0, 3, 6);
	addAnim("止まる2", 14, 0, 1, 0);
	addAnim("立ち1", 0, 1, 3, 8);
	addAnim("歩き1", 3, 1, 4, 4);
	addAnim("扇ぐ1", 7, 1, 4, 4);
	addAnim("落下1", 11, 4, 3, 3);
	addAnim("止まる1", 14, 1, 1, 0);
	addAnim("墜落", 0, 2, 4, 3);

	return true;
}

bool Player::clearFlag()
{
	return false;
}
void Player::GetKeyData()
{
	// Objを流用する
}
void Player::SetMove()
{
	bool moveLR = false;
	int animAdd = 0;
	GetKeyData();

	// 真ん中上(頭上)
	CHIP_TYPE cpTypeCT = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 0), BF_GP_GROUND);

	// 真ん中下(足元)
	CHIP_TYPE cpTypeCB = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 24 - 1), BF_GP_GROUND);

	// 左上
	CHIP_TYPE cpTypeLT = lpMapCtl.GetMapData(pos + VECTOR2(-1, 0), BF_GP_GROUND);

	// 左下
	CHIP_TYPE cpTypeLB = lpMapCtl.GetMapData(pos + VECTOR2(-1, 24 - 1), BF_GP_GROUND);

	// 右上
	CHIP_TYPE cpTypeRT = lpMapCtl.GetMapData(pos + VECTOR2(16 + 1, 0), BF_GP_GROUND);

	// 右下
	CHIP_TYPE cpTypeRB = lpMapCtl.GetMapData(pos + VECTOR2(16 + 1, 24 - 1), BF_GP_GROUND);

	// 自分の1マス上
	CHIP_TYPE cpTypeCU = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, -1), BF_GP_GROUND);

	// 自分の1マス下
	CHIP_TYPE cpTypeCD = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 24), BF_GP_GROUND);

	animCnt++;
	velocityY += 0.2f;
	pos.y += velocityY;
	pos.x += velocityX;
	SetAnim("落下2");

	if (velocityX >= 4)
	{
		velocityX = 4;
	}
	if (velocityX <= -4)
	{
		velocityX = -4;
	}
	if (velocityY >= 4)
	{
		velocityY = 4;
	}

	if (velocityX <= 0)
	{
		velocityX += 0.02f;
	}
	else if (velocityX >= 0)
	{
		velocityX -= 0.02f;
	}

	if(keydata	[KEY_INPUT_UP])
	{
		velocityY -= 0.5f;
	}
	if (keydata[KEY_INPUT_DOWN] == !keydataOld[KEY_INPUT_DOWN])
	{
		velocityY -= 1.0f;
	}
	if (cpTypeCD == BF_GP_GROUND)
	{
		if (velocityY <= 0)
		{
			velocityY = 0;
		}
		moveLR = true;
		SetAnim("立ち2");
		if (keydata[KEY_INPUT_LEFT])
		{
			velocityX -= 0.5f;
			dir = DIR_L;
		}
		if (keydata[KEY_INPUT_RIGHT])
		{
			velocityX += 0.5f;
			dir = DIR_R;
		}
	}
	if (cpTypeCD == BF_GP_WATER)
	{
		lpGameTask.CheckEditMode();
	}
	if ((cpTypeCD != BF_GP_GROUND))
	{
		moveLR = true;
		if (keydata[KEY_INPUT_LEFT])
		{
			SetAnim("扇ぐ2");
			velocityX -= 0.5f;
			pos.x += velocityX;
			dir = DIR_L;
		}
		if (keydata[KEY_INPUT_RIGHT])
		{
			SetAnim("扇ぐ2");
			velocityX += 0.5f;
			pos.x += velocityX;
			dir = DIR_R;
		}
	}
	if (pos.y <= 0)
	{
		velocityY = 2;
	}
	if (pos.x <= 0)
	{
		pos.x = ScreenSizeX;
	}
	else if(pos.x >= ScreenSizeX + 1)
	{
		pos.x = 0;
	}
	DrawFormatString(10, 10, 0xffffff, "X座標 %d", pos.x);
	DrawFormatString(10, 26, 0xffffff, "Y座標 %d", pos.y);
}

void Player::Draw()
{
	Obj::Draw();
}

char Player::KeyGetRng()
{
	return 0;
}
