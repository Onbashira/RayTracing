#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
private:

	Vector3 _center;

	float _radius;

	MaterialPtr _material;

public:

	Sphere();

	Sphere(const Vector3& centerPos, float rad, const MaterialPtr & mat);

	virtual ~Sphere();

	virtual bool Hit(const Ray& r, float t0, float t1, HitRec& hrec) const override;

	virtual float PdfValue(const Vector3& o, const Vector3& v) const override;

	virtual Vector3 Random(const Vector3& o) const override;

};

