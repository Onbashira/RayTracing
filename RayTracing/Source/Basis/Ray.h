#pragma once
#include "Source/Utility/MathUtil.h"
class Ray
{

public:

private:

	//!•ûŒü
	Vector3 _direction;
	//!Žn“_
	Vector3 _origin;

public:
	Ray() {};
	Ray(const Vector3& origin , const Vector3& dir) : _origin(origin), _direction(dir) {};

	const Vector3& Origin()const { return _origin; }
	const Vector3& Direction()const { return _direction; }
	Vector3 At(float t)const {
		//p(t) = o + tD.
		return _origin + (_direction * t);
	}

	~Ray() {};
};

