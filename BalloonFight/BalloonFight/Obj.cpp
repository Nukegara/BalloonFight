#include "DxLib.h"
#include "Obj.h"
#include "ImageMng.h"
#include"GameTask.h"


Obj::Obj(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 chipOffset) :keydata(_keydata), keydataOld(_keydataOld)
{
	animCnt			= 0;
	pos				= { 0, 0 };
	divCnt			= { 0, 0 };
	divSize			= { 0, 0 };
	chipOffset		= { 0, 0 };
}


Obj::~Obj()
{
	// delete imageID;
}

void Obj::Init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed)
{
	ImageMng::GetInstance()->GetID(filename, divSize, divCnt, chipOffset);
	imageName			= filename;
	this->divSize		= divSize;
	this->divCnt		= divCnt;
	this->chipOffset	= chipOffset;
	this->speed			= speed;
	initAnim();
}

bool Obj::initAnim()
{
	return true;
}

bool Obj::addAnim(std::string animName, int id_x, int id_y, int frame, int inv)
{
	anim[animName][ANIM_START] = id_x + id_y * divCnt.x;
	anim[animName][ANIM_FRAME] = frame;
	anim[animName][ANIM_INV]   = inv;
	return true;
}

bool Obj::Update()
{
	return false;
}

void Obj::Draw()
{
	if (imageName.length() == 0)
	{
		return;
	}
	VECTOR2 drawOffset = lpGameTask.GetDrawOffset();
	VECTOR2 areaOffset = lpGameTask.GetAreaOffset();

	int id = 0;
	if (anim.find(animName) != anim.end())
	{
		id = anim[animName][ANIM_START] + ((animCnt / anim[animName][ANIM_INV])% anim[animName][ANIM_FRAME]);
	}
	if (dir == DIR_L)
	{
		DrawGraph(pos.x + drawOffset.x + areaOffset.x, pos.y + drawOffset.y + areaOffset.y, IMAGE_ID(imageName)[id], true);
	}
	if (dir == DIR_R)
	{
		DrawTurnGraph(pos.x + drawOffset.x + areaOffset.x, pos.y + drawOffset.y + areaOffset.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw( int id)
{
	if (IMAGE_ID(imageName).size() <= (unsigned int) id)
	{
		return;
	}
	if (imageName.length() == 0)
	{
		return;
	}
	VECTOR2 drawOffset = lpGameTask.GetDrawOffset();
	VECTOR2 areaOffset = lpGameTask.GetAreaOffset();
	DrawGraph(pos.x/* + drawOffset.x + areaOffset.x*/, pos.y/* + drawOffset.y + areaOffset.y*/, IMAGE_ID(imageName)[id], true);
}

void Obj::SetPos(const VECTOR2 & pos)
{
	this->pos = pos;
}

const VECTOR2 & Obj::GetPos()
{
	return pos;
}

bool Obj::SetAnim(std::string animName)
{
	if (anim.find(animName) == anim.end())
	{
		return false;
	}
	if (Obj::animName != animName)
	{
		animCnt = 0;
		Obj::animName = animName;
	}
	Obj::animName = animName;
	return true;
}
