#pragma once
#include "Shape.h"

class FlipNormals : public Shape
{
	ShapePtr _shape;
public:
	FlipNormals(const ShapePtr& shape);
	virtual ~FlipNormals();

	virtual bool Hit(const Ray& r, float t0, float t1, HitRec& hrec) const override;
};

