#include "CosinePdf.h"



CosinePdf::CosinePdf()
{
}


CosinePdf::~CosinePdf()
{
}

float CosinePdf::Value(const HitRec & hrec, const Vector3 & dir) const
{
	float cosine = dot(normalize(dir), hrec.n);
	if (cosine > 0) {
		return cosine / F_PI;
	}
	else {
		return 0;
	}
}

Vector3 CosinePdf::Generate(const HitRec & hrec) const
{
	ONB uvw; uvw.build_from_w(hrec.n);
	Vector3 v = uvw.local(random_cosine_direction());
	return v;
}
