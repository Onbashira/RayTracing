#pragma once
#include "Shape.h"
#include "FlipNormals.h"
#include "Rect.h"
#include "ShapeList.h"
class Box :
	public Shape
{
private:
	Vector3 _p0;
	Vector3	_p1;
	std::unique_ptr<ShapeList> _list;
public:

	Box(const Vector3& p0, const Vector3& p1, const MaterialPtr& m);

	virtual ~Box();

	virtual bool Hit(const Ray& ray, float t0, float t1, HitRec& hrec)const;

};

