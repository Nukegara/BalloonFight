#pragma once
#include <vector>
#include "VECTOR2.h"

// �ð���ް��̏������݁A�ǂݍ��݁A�ۑ����s��

enum CHIP_TYPE
{
	BF_CHIP_BLANK,		// ��
	BF_CHIP_WATER1,		// ����
	BF_CHIP_WATER2,
	BF_CHIP_WATER3,
	BF_CHIP_WATER4,
	BF_CHIP_WATER5,		// ����
	BF_CHIP_WATER6,
	BF_CHIP_WATER7,
	BF_CHIP_WATER8,
	BF_CHIP_WATER9,		// �C��
	BF_CHIP_WATER10,
	BF_CHIP_WATER11,
	BF_CHIP_WATER12,
	BF_CHIP_GROUND1,	// ����
	BF_CHIP_GROUND2,
	BF_CHIP_GROUND3,
	BF_CHIP_GROUND4,
	BF_CHIP_GROUND5,
	BF_CHIP_GROUND6,
	BF_CHIP_PILLAR1,	// �Β�
	BF_CHIP_PILLAR2,
	BF_CHIP_PL,			// ��ڲ԰
	BF_CHIP_ENE,		// �G
	BF_CHIP_CNT_X
};

enum CHIP_GRP {
	BF_GP_WATER,		// ��
	BF_GP_GROUND,		// ����
	BF_GP_PILLAR,		// ��(�����蔻�薳��)
	BF_GP_CHAR,			// ��׸��(��ڲ԰, �G)
	BF_GP_RESERVE,		// �g�����̗\��
	BF_GP_MAX
};
struct DataHeader
{
	char fileID[13];		// ̧�ق�ID���
	unsigned char verID;	// ̧�ق��ް�ޮݔԍ�
	unsigned char rez1[2];	// �ײ��ĕ��\��̈�
	int sizeX;				// ϯ�߂̻���
	int sizeY;				// ϯ�߂̻���
	unsigned char rez2[3];	// �ײ��ĕ��\��̈�
	unsigned char sum;		// SUM�l
};

using VEC_CHIP = std::vector<unsigned int>;	// �ꎟ���z��
using VEC_CHIP2 = std::vector<VEC_CHIP>;	// �񎟌��z��

#define LAST_EDIT_CHIP (BF_CHIP_ENE)	// ��ި�ĂōŌ�Ɏg������
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

