#pragma once
#include "Obj.h"




class Player :
	public Obj
{
public:
	Player(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 _chip
	);
	~Player();
	virtual char KeyGetRng();
	bool Update();
	void Draw();
	void SetMove();

private:
	bool initAnim();
	bool clearFlag();
	float velocityX;
	float velocityY;

	virtual void GetKeyData();
};

