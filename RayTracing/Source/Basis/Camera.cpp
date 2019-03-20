#include "Camera.h"

Camera::Camera(const Vector3 & u, const Vector3 & v, const Vector3 & w)
{
	_origin = Vector3(0);
	_uvw[0] = u;
	_uvw[1] = v;
	_uvw[2] = w;
}

Camera::Camera(const Vector3 & lookfrom, const Vector3 & lookat, const Vector3 & vup, float vfov, float aspect)
{
	Vector3 u, v, w;
	_aspectRatio = aspect;
	_fov = vfov;
	float halfH = tanf(radians(vfov) / 2.0f);
	float halfW = aspect * halfH;

	_origin = lookfrom;
	w = normalize(lookfrom - lookat);
	u = normalize(cross( w , vup));
	v = cross(w, u);
	_uvw[2] = _origin - halfW * u - halfH * v - w;
	_uvw[0] = 2.0f * halfW * u;
	_uvw[1] = 2.0f * halfH * v;
}

Ray Camera::getRay(float u, float v) const
{
	return Ray(_origin, _uvw[2] + _uvw[0] * u + _uvw[1] * v - _origin);
}
