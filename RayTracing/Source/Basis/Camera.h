#pragma once
#include "Source/Utility/MathUtil.h"
#include "Source/Basis/Ray.h"

class Camera
{
public:

private:

	Vector3 _origin;  // 位置

	Vector3 _uvw[3];  // 直交基底ベクトル

	float _aspectRatio;

	float _fov;

public:

	Camera() {}

	Camera(const Vector3& u, const Vector3& v, const Vector3& w);

	Camera(const Vector3& lookfrom, const Vector3& lookat, const Vector3& vup, float vfov, float aspect);

	Ray getRay(float u, float v) const;
};

