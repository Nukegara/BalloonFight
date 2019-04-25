#pragma once
#include <string>
#include <vector>
#include <map>
#include "VECTOR2.h"

enum DIR_LR
{
	DIR_L,		// ���ړ�
	DIR_R,		// �E�ړ�
	DIR_MAX
};

enum ANIM
{
	ANIM_START,	// ��Ұ��݊J�n�ʒu��ID
	ANIM_FRAME,	// ��Ұ����ڰ�(�ς̐�)
	ANIM_INV,	// ��Ұ��ݲ������(�Ԋu)
	ANIM_MAX
};

class Obj
{
public:
	Obj(const char(&_keydata)[256], const char(&_keydataOld)[256], VECTOR2 chipOffset);
	~Obj();
	void Init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed);
	virtual bool Update() = 0;		// �X�V����
	virtual void Draw();			// �`��֐�
	void Draw( int id);

	void SetPos(const VECTOR2 & pos);

	const VECTOR2 &GetPos();
	bool SetAnim(std::string animName);

private:
	virtual bool initAnim();
	std::string imageName;
	VECTOR2 divSize;							// �`�����߂̻���
	VECTOR2 divCnt;								// �`�����߂̐�(�c��)
	VECTOR2 chipOffset;							// �`�����߲Ұ��ID�̓񎟌��z��
	std::map<std::string, int[ANIM_MAX]> anim;	// ��Ұ��݂̼��ݽ���̓�����ð���
	std::string animName;						// ���݂̑I������Ă����Ұ���

protected:
	bool addAnim(std::string animName, int id_x, int id_y, int frame, int inv);
	const char(&keydata)[256];
	const char(&keydataOld)[256];
	VECTOR2 pos;		// �`��ʒu
	int speed;			// �ړ���
	unsigned int animCnt;
	DIR_LR dir;
};

