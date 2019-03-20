#pragma once
#include "Source/Utility/MathUtil.h"
#include "Source/Basis/Ray.h"
#include "Source/Basis/HitRec.h"
#include <memory>
class Shape
{
public:
	
	Shape();
	
	virtual ~Shape();

	virtual bool Hit(const Ray& ray, float t0, float t1, HitRec& hrec)const = 0;

	virtual float PdfValue(const Vector3& o, const Vector3& v) const { return 0; }

	virtual Vector3 Random(const Vector3& o) const { return Vector3(1.0f, 0.0f, 0.0f); }

};

typedef  std::shared_ptr<Shape> ShapePtr;
