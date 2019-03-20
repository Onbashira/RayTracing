#include "FlipNormals.h"

FlipNormals::FlipNormals(const ShapePtr & shape) : _shape(shape)
{
}

FlipNormals::~FlipNormals()
{
}

bool FlipNormals::Hit(const Ray & r, float t0, float t1, HitRec & hrec) const
{
	if (_shape->Hit(r, t0, t1, hrec)) {
		hrec.n = -hrec.n;
		return true;
	}
	else {
		return false;
	}
}
