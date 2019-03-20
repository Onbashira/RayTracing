#pragma once
#include "Shape.h"
class Rect : public Shape
{
	
public:
	enum AxisType {
		XY = 0,
		XZ,
		YZ,
	};

private:

	float _x0;
	float _x1;
	float _y0;
	float _y1;

	float _k;
	AxisType _axis;
	MaterialPtr _material;

public:
	
	Rect(float x0,float x1,float y0,float y1,float k, AxisType axis,
		const MaterialPtr& material);
	
	virtual ~Rect();

	virtual bool Hit(const Ray& ray, float t0, float t1, HitRec& hrec)const;

	virtual float PdfValue(const Vector3& o, const Vector3& v) const;

	virtual Vector3 Random(const Vector3& o) const;

};

