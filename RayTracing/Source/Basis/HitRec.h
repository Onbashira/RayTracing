#pragma once
#include "Source/Utility/MathUtil.h"
#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialPtr;

class HitRec
{
public:
	//光線パラメータ
	float t;
	//テクスチャUV
	float u;
	//テクスチャUV
	float v;
	//衝突した位置
	Vector3 p;
	//衝突した位置の法線
	Vector3 n;
	//マテリアルの参照
	MaterialPtr mat;
private:

public:
	HitRec();
	~HitRec();
};

