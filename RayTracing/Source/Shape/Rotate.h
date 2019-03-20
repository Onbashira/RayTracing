#pragma once
#include "Shape.h"

class Rotate : public Shape {
public:
	Rotate(const ShapePtr& sp, const Vector3& axis, float angle)
		: _shape(sp)
		, _quat(Quat::rotation(radians(angle), axis)) {
	}

	virtual bool Hit(const Ray& r, float t0, float t1, HitRec& hrec) const override;

private:
	ShapePtr _shape;
	Quat _quat;
};

