#include "Rotate.h"


bool Rotate::Hit(const Ray & r, float t0, float t1, HitRec & hrec) const
{
	Quat revq = conj(_quat);
	Vector3 origin = rotate(revq, r.Origin());
	Vector3 direction = rotate(revq, r.Direction());
	Ray rot_r(origin, direction);
	if (_shape->Hit(rot_r, t0, t1, hrec)) {
		hrec.p = rotate(_quat, hrec.p);
		hrec.n = rotate(_quat, hrec.n);
		return true;
	}
	else {
		return false;
	}
}
