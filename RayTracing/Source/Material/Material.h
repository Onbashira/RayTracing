#pragma once
#include "Source/Basis/Ray.h"
#include "Source/Basis/HitRec.h"
#include "Source/Basis/ScatterRec.h"

class Material
{
public:
	Material();
	virtual ~Material();

	virtual bool Scatter(const Ray& ray, const HitRec& hitRec, ScatterRec& scatterRec)const = 0;

	virtual Vector3 Emitted(const Ray& r, const HitRec& hrec) const { return Vector3(0); }

	virtual float ScatteringPdf(const Ray& r, const HitRec& hrec) const { return 0.0f; };

};