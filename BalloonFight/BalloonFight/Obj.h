#pragma once
#include <string>
#include <vector>
#include <map>
#include "VECTOR2.h"

enum DIR_LR
{
	DIR_L,		// 左移動
	DIR_R,		// 右移動
	DIR_MAX
};

enum ANIM
{
	ANIM_START,	// ｱﾆﾒｰｼｮﾝ開始位置のID
	ANIM_FRAME,	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ(ｺﾏの数)
	ANIM_INV,	// ｱﾆﾒｰｼｮﾝｲﾝﾀｰﾊﾞﾙ(間隔)
	ANIM_MAX
};

class Obj
{
public:
	Obj(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 chipOffset);
	~Obj();
	void Init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed);
	virtual bool Update() = 0;		// 更新処理
	virtual void Draw();			// 描画関数
	void Draw( int id);

	void SetPos(const VECTOR2 & pos);

	const VECTOR2 &GetPos();
	bool SetAnim(std::string animName);

private:
	virtual bool initAnim();
	std::string imageName;
	VECTOR2 divSize;							// 描画ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 divCnt;								// 描画ﾁｯﾌﾟの数(縦横)
	VECTOR2 chipOffset;							// 描画ﾁｯﾌﾟｲﾒｰｼﾞIDの二次元配列
	std::map<std::string, int[ANIM_MAX]> anim;	// ｱﾆﾒｰｼｮﾝのｼｰｹﾝｽ情報の入ったﾃｰﾌﾞﾙ
	std::string animName;						// 現在の選択されているｱﾆﾒｰｼｮﾝ

protected:
	bool addAnim(std::string animName, int id_x, int id_y, int frame, int inv);
	const char(&keydata)[256];
	const char(&keydataOld)[256];
	VECTOR2 pos;		// 描画位置
	int speed;			// 移動量
	unsigned int animCnt;
	DIR_LR dir;
};

