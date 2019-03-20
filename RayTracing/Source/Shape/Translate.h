#pragma once
#include "Shape.h"
class Translate :
	public Shape
{

private:
	ShapePtr _shape;
	Vector3 _offset;
public:
	Translate(const ShapePtr& sp, const Vector3& displacement)
		: _shape(sp)
		, _offset(displacement) {
	}

	virtual bool Hit(const Ray& ray, float t0, float t1, HitRec& hrec) const override;


};

