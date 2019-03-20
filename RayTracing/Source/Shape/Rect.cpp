#include "Rect.h"



Rect::Rect(float x0, float x1, float y0, float y1, float k, AxisType axis ,const MaterialPtr& material) :
	_x0(x0),_x1(x1),_y0(y0),_y1(y1),_k(k),_axis(axis),_material(material)
{

}

Rect::~Rect()
{

}

bool Rect::Hit(const Ray & ray, float t0, float t1, HitRec & hrec) const
{
	int xi = 0, yi = 0, zi = 0;
	Vector3 axis;
	switch (_axis) {
	case XY: xi = 0; yi = 1; zi = 2; axis = Vector3::zAxis(); break;
	case XZ: xi = 0; yi = 2; zi = 1; axis = Vector3::yAxis(); break;
	case YZ: xi = 1; yi = 2; zi = 0; axis = Vector3::xAxis(); break;
	}

	float t = (_k - ray.Origin()[zi]) / ray.Direction()[zi];
	if (t < t0 || t > t1) {
		return false;
	}

	float x = ray.Origin()[xi] + t * ray.Direction()[xi];
	float y = ray.Origin()[yi] + t * ray.Direction()[yi];
	if (x < _x0 || x > _x1 || y < _y0 || y > _y1) {
		return false;
	}

	hrec.u = (x - _x0) / (_x1 - _x0);
	hrec.v = (y - _y0) / (_y1 - _y0);
	hrec.t = t;
	hrec.mat = _material;
	hrec.p = ray.At(t);
	hrec.n = axis;
	return true;
}

float Rect::PdfValue(const Vector3 & o, const Vector3 & v) const
{
	if (_axis != XZ) return 0;
	HitRec hrec;
	if (this->Hit(Ray(o, v), 0.001f, FLT_MAX, hrec)) {
		float area = (_x1 - _x0) * (_y1 - _y0);
		float distance_squared = pow2(hrec.t) * lengthSqr(v);
		float cosine = fabs(dot(v, hrec.n)) / length(v);
		return distance_squared / (cosine * area);
	}
	else {
		return 0;
	}
}

Vector3 Rect::Random(const Vector3 & o) const
{
	if (_axis != XZ) return Vector3(1, 0, 0);
	float x = _x0 + drand48()*(_x1 - _x0);
	float y = _y0 + drand48()*(_y1 - _y0);
	Vector3 random_point;
	switch (_axis) {
	case XY:
		random_point = Vector3(x, y, _k);
		break;
	case XZ:
		random_point = Vector3(x, _k, y);
		break;
	case YZ:
		random_point = Vector3(_k, x, y);
		break;
	}
	Vector3 v = random_point - o;
	return v;
}
