#pragma once
#include "Shape.h"
#include <vector>
#include <memory>
typedef std::shared_ptr<Shape> ShapePtr;

class ShapeList : public Shape
{
private:
	std::vector<ShapePtr> _list;

public:

	ShapeList();

	virtual ~ShapeList();

	void Add(const ShapePtr& shape);

	virtual bool Hit(const Ray& r, float t0, float t1, HitRec& hrec) const override;

	virtual float PdfValue(const Vector3& o, const Vector3& v) const;

	virtual Vector3 Random(const Vector3& o) const;

private:
};

