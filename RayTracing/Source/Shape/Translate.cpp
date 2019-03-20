#include "Translate.h"




bool Translate::Hit(const Ray & ray, float t0, float t1, HitRec & hrec) const
{
	Ray moveRay(ray.Origin() - _offset, ray.Direction());
	if (_shape->Hit(moveRay, t0, t1, hrec)) {
		hrec.p += _offset;
		return true;
	}
	else {
		return false;
	}
}
