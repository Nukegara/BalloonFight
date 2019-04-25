#pragma once
#include <map>
#include <vector>
#include "VECTOR2.h"

using VEC_INT = std::vector<int>;
#define IMAGE_ID(X) (ImageMng::GetInstance()->GetID(X))

class ImageMng
{
public:
	static void Create();
	static void Destroy();
	static ImageMng *GetInstance()
	{
		Create();
		return s_Instance;
	}
	const VEC_INT & GetID(std::string f_name);														// �P��摜�ǂݍ���(LoadGraph)
	const VEC_INT & GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset);	// �����摜�ǂݍ���(LoadDivGraph)

private:
	ImageMng();
	~ImageMng();

	static ImageMng *s_Instance;
	// std::map<���̌^, �A�z�z��̌^> �A�z�z��;
	std::map<std::string, VEC_INT> imgMap;
};
