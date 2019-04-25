#include "DxLib.h"
#include "Enemy.h"
#include "mapControl.h"

Enemy::Enemy(std::weak_ptr<Obj> target, VECTOR2 chipOffset) : Player(keyData, keyDataOld, chipOffset)
{
	for (int i = 0; i < sizeof(keydata); i++)
	{
		keyData[i] = 0;
		keyDataOld[i] = 0;
	}
	this->target = target;
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	Obj::Draw();
}

void Enemy::GetKeyData()
{
	// ¶‰º
	CHIP_TYPE cpTypeLB = lpMapCtl.GetMapData(pos + VECTOR2(-1, lpMapCtl.GetChipSize() - 1), BF_GP_WATER);
	// ‰E‰º
	CHIP_TYPE cpTypeRB = lpMapCtl.GetMapData(pos + VECTOR2(lpMapCtl.GetChipSize() + 1, lpMapCtl.GetChipSize() - 1), BF_GP_WATER);

	if (target.expired())
	{
		return;
	}
	VECTOR2 Ppos;
	VECTOR2 Epos;
	keyData[KEY_INPUT_LEFT]  = false;
	keyData[KEY_INPUT_RIGHT] = false;
	keyData[KEY_INPUT_UP]    = false;
	keyData[KEY_INPUT_DOWN]  = false;
	Ppos.x = target.lock()->GetPos().x;
	Ppos.y = target.lock()->GetPos().y;
	Epos.x = pos.x;
	Epos.y = pos.y;

	//if (Ppos.y == Epos.y)
	{
		if (Ppos.x < Epos.x)
		{
			keyData[KEY_INPUT_LEFT] = true;
		}
		if (Ppos.x > Epos.x)
		{
			keyData[KEY_INPUT_RIGHT] = true;
		}
	}
}

bool Enemy::Update()
{
	Player::SetMove();
	return false;
}
