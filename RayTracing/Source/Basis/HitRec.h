#pragma once
#include "Source/Utility/MathUtil.h"
#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialPtr;

class HitRec
{
public:
	//�����p�����[�^
	float t;
	//�e�N�X�`��UV
	float u;
	//�e�N�X�`��UV
	float v;
	//�Փ˂����ʒu
	Vector3 p;
	//�Փ˂����ʒu�̖@��
	Vector3 n;
	//�}�e���A���̎Q��
	MaterialPtr mat;
private:

public:
	HitRec();
	~HitRec();
};

