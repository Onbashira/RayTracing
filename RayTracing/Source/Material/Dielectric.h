#pragma once
#include "Material.h"
class Dielectric : public Material
{
public:

private:

	float _ri;
public:

	Dielectric();

	Dielectric(float ri) : _ri(ri){};

	virtual ~Dielectric();

	virtual bool Scatter(const Ray& ray, const HitRec& hrec, ScatterRec& srec)const override;

};

