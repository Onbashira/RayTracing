#pragma once
#include "Source/Utility/MathUtil.h"
#include "Source/Basis/HitRec.h"

//確率密度関数　ベース
class Pdf
{
public:
	Pdf();
	virtual ~Pdf();
	
	virtual float Value(const HitRec& hrec, const Vector3& dir)const = 0;
	virtual Vector3 Generate(const HitRec& hrec)const = 0;
};

