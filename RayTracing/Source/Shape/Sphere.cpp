#include "Sphere.h"



Sphere::Sphere()
{
}

Sphere::Sphere(const Vector3 & centerPos, float rad, const MaterialPtr & mat) :
	_center(centerPos), _radius(rad), _material(mat)
{

}


Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray & r, float t0, float t1, HitRec & hrec) const
{
	///t=−b−D√2a
	Vector3 oc = r.Origin() - _center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0f*dot(oc, r.Direction());
	float c = dot(oc, oc) - pow2(_radius);
	float D = b * b - 4 * a*c;
	if (D > 0) {
		float root = sqrtf(D);
		float temp = (-b - root) / (2.0f*a);
		if (temp < t1 && temp > t0) {
			hrec.t = temp;
			hrec.p = r.At(hrec.t);
			hrec.n = (hrec.p - _center) / _radius;
			hrec.mat = _material;
			get_sphere_uv(hrec.p, hrec.u, hrec.v);

			return true;
		}
		temp = (-b + root) / (2.0f*a);
		if (temp < t1 && temp > t0) {
			hrec.t = temp;
			hrec.p = r.At(hrec.t);
			hrec.n = (hrec.p - _center) / _radius;
			hrec.mat.operator=(_material);
			get_sphere_uv(hrec.p, hrec.u, hrec.v);

			return true;
		}
	}

	return false;
}

float Sphere::PdfValue(const Vector3 & o, const Vector3 & v) const
{
	HitRec hrec;
	if (this->Hit(Ray(o, v), 0.001f, FLT_MAX, hrec)) {
		float dd = lengthSqr(_center - o);
		float rr = std::min(pow2(_radius), dd);
		float cos_theta_max_sq = 1.0f - rr * recip(dd);
		float cos_theta_max = sqrtf(cos_theta_max_sq);
		float solid_angle = F_2PI * (1.0f - cos_theta_max);
		return recip(solid_angle);
	}
	else {
		return 0;
	}
}

Vector3 Sphere::Random(const Vector3 & o) const
{
	Vector3 direction = _center - o;
	float distance_squared = lengthSqr(direction);
	ONB uvw; uvw.build_from_w(direction);
	Vector3 v = uvw.local(random_to_sphere(_radius, distance_squared));
	return v;
}


