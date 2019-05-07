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
	addAnim("����2", 0, 0, 3, 8);
	addAnim("����2", 3, 0, 4, 4);
	addAnim("�2", 7, 0, 4, 6);
	addAnim("����2", 11, 0, 3, 6);
	addAnim("�~�܂�2", 14, 0, 1, 0);
	addAnim("����1", 0, 1, 3, 8);
	addAnim("����1", 3, 1, 4, 4);
	addAnim("�1", 7, 1, 4, 4);
	addAnim("����1", 11, 4, 3, 3);
	addAnim("�~�܂�1", 14, 1, 1, 0);
	addAnim("�ė�", 0, 2, 4, 3);

	return true;
}

bool Player::clearFlag()
{
	return false;
}
void Player::GetKeyData()
{
	// Obj�𗬗p����
}
void Player::SetMove()
{
	bool moveLR = false;
	int animAdd = 0;
	GetKeyData();

	// �^�񒆏�(����)
	CHIP_TYPE cpTypeCT = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 0), BF_GP_GROUND);

	// �^�񒆉�(����)
	CHIP_TYPE cpTypeCB = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 24 - 1), BF_GP_GROUND);

	// ����
	CHIP_TYPE cpTypeLT = lpMapCtl.GetMapData(pos + VECTOR2(-1, 0), BF_GP_GROUND);

	// ����
	CHIP_TYPE cpTypeLB = lpMapCtl.GetMapData(pos + VECTOR2(-1, 24 - 1), BF_GP_GROUND);

	// �E��
	CHIP_TYPE cpTypeRT = lpMapCtl.GetMapData(pos + VECTOR2(16 + 1, 0), BF_GP_GROUND);

	// �E��
	CHIP_TYPE cpTypeRB = lpMapCtl.GetMapData(pos + VECTOR2(16 + 1, 24 - 1), BF_GP_GROUND);

	// ������1�}�X��
	CHIP_TYPE cpTypeCU = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, -1), BF_GP_GROUND);

	// ������1�}�X��
	CHIP_TYPE cpTypeCD = lpMapCtl.GetMapData(pos + VECTOR2(16 / 2, 24), BF_GP_GROUND);

	animCnt++;
	velocityY += 0.2f;
	pos.y += velocityY;
	pos.x += velocityX;
	SetAnim("����2");

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
		SetAnim("����2");
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
			SetAnim("�2");
			velocityX -= 0.5f;
			pos.x += velocityX;
			dir = DIR_L;
		}
		if (keydata[KEY_INPUT_RIGHT])
		{
			SetAnim("�2");
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
	DrawFormatString(10, 10, 0xffffff, "X���W %d", pos.x);
	DrawFormatString(10, 26, 0xffffff, "Y���W %d", pos.y);
}

void Player::Draw()
{
	Obj::Draw();
}

char Player::KeyGetRng()
{
	return 0;
}
