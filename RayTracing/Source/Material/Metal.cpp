#include "Metal.h"
#include "Source/Utility/MathUtil.h"


Metal::Metal()
{
}


Metal::~Metal()
{
}

bool Metal::Scatter(const Ray & ray, const HitRec & hrec, ScatterRec & srec) const
{
	Vector3 reflected = reflect(normalize(ray.Direction()), hrec.n);
	reflected += _raoughness * random_in_unit_sphere();
	srec.ray = Ray(hrec.p, reflected);
	srec.albedo = _albedo->Value(hrec.u, hrec.v, hrec.p);
	srec.pdfValue = nullptr;
	srec.isSpecular = true;
	return dot(srec.ray.Direction(), hrec.n) > 0;
}
