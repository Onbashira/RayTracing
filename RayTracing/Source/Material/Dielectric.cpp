#include "Dielectric.h"



Dielectric::Dielectric()
{
}


Dielectric::~Dielectric()
{
}

bool Dielectric::Scatter(const Ray & ray, const HitRec & hrec, ScatterRec & srec) const
{
	srec.isSpecular = true;

	Vector3 outward_normal;
	Vector3 reflected = reflect(ray.Direction(), hrec.n);
	float ni_over_nt;
	float reflect_prob;
	float cosine;
	if (dot(ray.Direction(), hrec.n) > 0) {
		outward_normal = -hrec.n;
		ni_over_nt = _ri;
		cosine = _ri * dot(ray.Direction(), hrec.n) / length(ray.Direction());
	}
	else {
		outward_normal = hrec.n;
		ni_over_nt = recip(_ri);
		cosine = -dot(ray.Direction(), hrec.n) / length(ray.Direction());
	}

	srec.albedo = Vector3(1.0f);

	Vector3 refracted;
	if (refract(-ray.Direction(), outward_normal, ni_over_nt, refracted)) {
		reflect_prob = schlick(cosine, _ri);
	}
	else {
		reflect_prob = 1.0f;
	}

	if (drand48() < reflect_prob) {
		srec.ray = Ray(hrec.p, reflected);
	}
	else {
		srec.ray = Ray(hrec.p, refracted);
	}

	return true;


}
