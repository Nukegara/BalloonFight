#pragma once
#include <memory>
#include "Player.h"
class Enemy :
	public Player
{
public:
	Enemy(std::weak_ptr<Obj> target, VECTOR2 _chipOffset);
	~Enemy();
	void Draw();
	virtual void GetKeyData();
	bool Update();
private:
	std::weak_ptr<Obj> target;
	char keyData[256];
	char keyDataOld[256];
};
