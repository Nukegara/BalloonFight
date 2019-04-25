#pragma once
#include <vector>
#include "VECTOR2.h"

// ｽﾃｰｼﾞﾃﾞｰﾀの書き込み、読み込み、保存を行う

enum CHIP_TYPE
{
	BF_CHIP_BLANK,		// 空白
	BF_CHIP_WATER1,		// 水面
	BF_CHIP_WATER2,
	BF_CHIP_WATER3,
	BF_CHIP_WATER4,
	BF_CHIP_WATER5,		// 水中
	BF_CHIP_WATER6,
	BF_CHIP_WATER7,
	BF_CHIP_WATER8,
	BF_CHIP_WATER9,		// 海面
	BF_CHIP_WATER10,
	BF_CHIP_WATER11,
	BF_CHIP_WATER12,
	BF_CHIP_GROUND1,	// 足場
	BF_CHIP_GROUND2,
	BF_CHIP_GROUND3,
	BF_CHIP_GROUND4,
	BF_CHIP_GROUND5,
	BF_CHIP_GROUND6,
	BF_CHIP_PILLAR1,	// 石柱
	BF_CHIP_PILLAR2,
	BF_CHIP_PL,			// ﾌﾟﾚｲﾔｰ
	BF_CHIP_ENE,		// 敵
	BF_CHIP_CNT_X
};

enum CHIP_GRP {
	BF_GP_WATER,		// 水
	BF_GP_GROUND,		// 足場
	BF_GP_PILLAR,		// 柱(当たり判定無し)
	BF_GP_CHAR,			// ｷｬﾗｸﾀｰ(ﾌﾟﾚｲﾔｰ, 敵)
	BF_GP_RESERVE,		// 拡張時の予約
	BF_GP_MAX
};
struct DataHeader
{
	char fileID[13];		// ﾌｧｲﾙのID情報
	unsigned char verID;	// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ番号
	unsigned char rez1[2];	// ｱﾗｲﾒﾝﾄ分予約領域
	int sizeX;				// ﾏｯﾌﾟのｻｲｽﾞ
	int sizeY;				// ﾏｯﾌﾟのｻｲｽﾞ
	unsigned char rez2[3];	// ｱﾗｲﾒﾝﾄ分予約領域
	unsigned char sum;		// SUM値
};

using VEC_CHIP = std::vector<unsigned int>;	// 一次元配列
using VEC_CHIP2 = std::vector<VEC_CHIP>;	// 二次元配列

#define LAST_EDIT_CHIP (BF_CHIP_ENE)	// ｴﾃﾞｨｯﾄで最後に使うﾁｯﾌﾟ
#define lpMapCtl				mapControl::GetInstance()
#define SET_MAP_ID(X, Y)		lpMapCtl.SetMapData(X, Y)
#define GET_CHIP_SIZE			lpMapCtl.GetChipSize()
#define GET_MAP_ID(X, Z)		lpMapCtl.GetMapData(X, Z)
#define GET_MAP_ID2(X, Y, Z)	lpMapCtl.GetMapData(X, Y, Z)

#define DATA_BIT_LEN (8)

class mapControl
{
public:
	static void Create();
	static void Destroy();
	static mapControl &GetInstance()
	{
		Create();
		return *s_Instance;
	}
	bool SetMapData(VECTOR2 pos, CHIP_TYPE id);
	CHIP_TYPE GetMapData(VECTOR2 pos, CHIP_GRP gpid);
	CHIP_TYPE GetMapData(int x, int y, CHIP_GRP gpid);
	bool MapSave();
	bool MapLoad();
	void MapDraw();
	int GetChipSize();
	VECTOR2 GetViewAreaSize();
	void MapInit();
	void SetUpChar();

private:
	mapControl();
	~mapControl();
	static mapControl *s_Instance;
	VEC_CHIP2 mapID;
	CHIP_GRP chipGp[BF_CHIP_CNT_X];
};

