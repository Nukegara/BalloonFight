#include "DxLib.h"
#include <direct.h>
#include "mapControl.h"
#include "GameTask.h"
#include "ImageMng.h"
#include "Player.h"
#include "Enemy.h"



constexpr int chipSize = 16;
constexpr int charSizeX = 16;
constexpr int charSizeY = 24;
constexpr int areaCntX = (ScreenSizeX / chipSize);
constexpr int areaCntY = (ScreenSizeY / chipSize);
#define BF_ID_NAME "BF_MAP_DATA"	// Ãß≤ŸÇÃIDèÓïÒíËã`
#define BF_ID_VER	0x01			// Ãß≤ŸÇÃ ﬁ∞ºﬁÆ›î‘çÜ

mapControl *mapControl::s_Instance = nullptr;

void mapControl::Create()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new mapControl();
	}
}

void mapControl::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

bool mapControl::SetMapData(VECTOR2 pos, CHIP_TYPE id)
{
	VECTOR2 tmpPos = (pos / chipSize);
	if (tmpPos.x < 0 || tmpPos.y < 0)
	{
		return false;
	}
	if (tmpPos.y >= (int)mapID.size())
	{
		return false;
	}
	if (tmpPos.x >= (int)mapID[tmpPos.y].size())
	{
		return false;
	}

	//int a = (CHIP_TYPE)(id << chipGp[id] * DATA_BIT_LEN);
	//(~a);
	//(a & 010101011100);
	//(a | 010101011100);
	mapID[tmpPos.y][tmpPos.x]
		= (mapID[tmpPos.y][tmpPos.x] &
		(~(0x000000ff/* << chipGp[id] * DATA_BIT_LEN*/)))
		| (id/* << chipGp[id] * DATA_BIT_LEN*/);

	return true;
}

CHIP_TYPE mapControl::GetMapData(VECTOR2 pos, CHIP_GRP gpid)
{
	VECTOR2 tmpPos(pos / chipSize);
	if (tmpPos.y >= (int)mapID.size())
	{
		return BF_CHIP_BLANK;
	}
	if (tmpPos.x >= (int)mapID.size())
	{
		return BF_CHIP_BLANK;
	}

	return (CHIP_TYPE)(mapID[tmpPos.y][tmpPos.x] >> (gpid/* * DATA_BIT_LEN) &0xff*/));
	//return (CHIP_TYPE)(mapID[tmpPos.y][tmpPos.x] = (gpid >> (CHIP_TYPE)chipGp[gpid] * DATA_BIT_LEN) & 0xff);
}

CHIP_TYPE mapControl::GetMapData(int x, int y, CHIP_GRP gpid)
{
	if (y < 0 || x < 0)
	{
		return BF_CHIP_BLANK;
	}
	if (y >= (int)mapID[y].size())
	{
		return BF_CHIP_BLANK;
	}
	if (x >= (int)mapID[y].size())
	{
		return BF_CHIP_BLANK;
	}
	return (CHIP_TYPE)(mapID[y][x] >> (gpid * DATA_BIT_LEN) &0xff);
}

bool mapControl::MapSave()
{
	DataHeader expData =
	{
		BF_ID_NAME,
		BF_ID_VER,
		{ 0, 0 },
		chipSize,
		chipSize,
		{ 0, 0, 0 },
		0x00
	};

	for (unsigned int y = 0; y < mapID.size(); y++)
	{
		for (unsigned int x = 0; x < mapID[y].size(); x++)
		{
			expData.sum += mapID[y][x];
		}
	}
	// F1Ç≈æ∞Ãﬁ
	// F2Ç≈€∞ƒﬁ	
	FILE *file;
	fopen_s(&file, "data/mapdata.map", "wb");
	fwrite(&expData, sizeof(DataHeader), 1, file);
	for (unsigned int y = 0; y < mapID.size(); y++)
	{
		fwrite(&mapID[y][0], mapID[y].size() * sizeof(unsigned int), 1, file);
	}

	fclose(file);
	return true;
}

bool mapControl::MapLoad()
{
	bool rtnFlag = true;
	FILE *file;
	DataHeader expData;
	fopen_s(&file, "data/mapdata.map", "rb");
	fread(&expData, sizeof(expData), 1, file);
	for (unsigned int y = 0; y < mapID.size(); y++)
	{
		fread(&mapID[y][0], mapID[y].size() * sizeof(unsigned int), 1, file);
	}

	SetUpChar();

	fclose(file);
	return rtnFlag;
}

void mapControl::MapDraw()
{
	int drawPosX = -chipSize;
	ClsDrawScreen();
	for (CHIP_GRP gp = BF_GP_WATER; gp < BF_GP_MAX; gp = (CHIP_GRP)(gp + 1))
	{
		for (int y = 0; y < areaCntY; y++)
		{
			for (int x = drawPosX; x < areaCntX/* + drawPosX*/; x++)
			{
				if (GET_MAP_ID2(x, y, gp) != BF_CHIP_BLANK)
				{
					CHIP_TYPE tmp = GET_MAP_ID2(x, y, gp);
					switch (tmp)
					{
					case BF_CHIP_BLANK:
					case BF_CHIP_PL:
					case BF_CHIP_ENE:
						if (!lpGameTask.CheckEditMode())	// πﬁ∞—”∞ƒﬁéûÇ…îÒï\é¶
						{
							break;
						}
					case BF_CHIP_WATER1:
					case BF_CHIP_WATER2:
					case BF_CHIP_WATER3:
					case BF_CHIP_WATER4:
					case BF_CHIP_WATER5:
					case BF_CHIP_WATER6:
					case BF_CHIP_WATER7:
					case BF_CHIP_WATER8:
					case BF_CHIP_WATER9:
					case BF_CHIP_WATER10:
					case BF_CHIP_WATER11:
					case BF_CHIP_GROUND1:
					case BF_CHIP_GROUND2:
					case BF_CHIP_GROUND3:
					case BF_CHIP_GROUND4:
					case BF_CHIP_GROUND5:
					case BF_CHIP_GROUND6:
					case BF_CHIP_PILLAR1:
					case BF_CHIP_PILLAR2:
						DrawGraph(x * GET_CHIP_SIZE, y * GET_CHIP_SIZE, IMAGE_ID("image/stage3.png")[GET_MAP_ID2(x, y, gp)], true);
						break;
					default:
						// ó·äOÇÃéûÇÕâΩÇ‡ÇµÇ»Ç¢
						break;
					}
				}
			}
		}
	}
}

int mapControl::GetChipSize()
{
	return chipSize;
}

VECTOR2 mapControl::GetViewAreaSize()
{
	return VECTOR2(areaCntX, areaCntY);
}

void mapControl::MapInit()
{

}

void mapControl::SetUpChar()
{
	std::list<obj_ptr>::iterator player;
	std::list<obj_ptr>::iterator enemy;

	if (!lpGameTask.CheckEditMode())
	{
		for (CHIP_GRP gp = BF_GP_WATER; gp < BF_GP_MAX; gp = (CHIP_GRP)(gp + 1))
		{
			for (int y = 0; y < areaCntY; y++)
			{
				for (int x = 0; x < areaCntX; x++)
				{
					// Ãﬂ⁄≤‘∞
					if (GET_MAP_ID2(x, y, gp) == BF_CHIP_PL)
					{
						// ObjListÇ…èÓïÒÇí«â¡ÇµÇƒitrÇ…èÓïÒÇó^Ç¶ÇÈ
						player = lpGameTask.addObjList(std::make_shared<Player>(lpGameTask.keyData, lpGameTask.keyDataOld, VECTOR2(0, 0)));
						(*player)->Init("image/player.png", { 16, 24 }, { 16, 3 }, { 1, 0 }, 2);
						(*player)->SetPos(VECTOR2(16 * x, 24 * y));
					}
				}
			}
		}
		for (CHIP_GRP gp = BF_GP_WATER; gp < BF_GP_MAX; gp = (CHIP_GRP)(gp + 1))
		{
			for (int y = 0; y < areaCntY; y++)
			{
				for (int x = 0; x < areaCntX; x++)
				{
					//	ìG
					if (GET_MAP_ID2(x, y, gp) == BF_CHIP_ENE)
					{
						enemy = lpGameTask.addObjList(std::make_shared<Enemy>((*player), VECTOR2(0, 0)));
						(*enemy)->Init("image/enemy.png", { 16, 24 }, { 16, 1 }, { 1, 0 }, 1);
						(*enemy)->SetPos(VECTOR2(24 * x, 16 * y));
					}
				}
			}
		}
	}
}

mapControl::mapControl()
{
	mapID.resize(areaCntY);
	for (int y = 0; y < areaCntY; y++)
	{
		mapID[y].resize(areaCntX);
	}
	chipGp[BF_CHIP_WATER1] = BF_GP_WATER;		// êÖ
	chipGp[BF_CHIP_WATER2] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER3] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER4] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER5] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER6] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER7] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER8] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER9] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER10] = BF_GP_WATER;
	chipGp[BF_CHIP_WATER11] = BF_GP_WATER;
	chipGp[BF_CHIP_GROUND1] = BF_GP_GROUND;		// ó§ÅAë´èÍ
	chipGp[BF_CHIP_GROUND2] = BF_GP_GROUND;
	chipGp[BF_CHIP_GROUND3] = BF_GP_GROUND;
	chipGp[BF_CHIP_GROUND4] = BF_GP_GROUND;
	chipGp[BF_CHIP_GROUND5] = BF_GP_GROUND;
	chipGp[BF_CHIP_GROUND6] = BF_GP_GROUND;
	chipGp[BF_CHIP_PILLAR1] = BF_GP_PILLAR;		// êŒíå
	chipGp[BF_CHIP_PILLAR2] = BF_GP_PILLAR;
	chipGp[BF_CHIP_ENE] = BF_GP_CHAR;			// Ãﬂ⁄≤‘∞ÅAìG
	chipGp[BF_CHIP_PL] = BF_GP_CHAR;
}


mapControl::~mapControl()
{
}
