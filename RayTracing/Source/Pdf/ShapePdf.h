#pragma once
#include "Source/Pdf/Pdf.h"
#include "Source/Shape/Shape.h"
class ShapePdf : public Pdf {

private:
	const Shape* _ptr;
	Vector3 _origin;
public:
	ShapePdf(const Shape* p, const Vector3& origin) : _ptr(p), _origin(origin) {
	}

	virtual float Value(const HitRec& hrec, const Vector3& direction) const override {
		return _ptr->PdfValue(_origin, direction);
	}

	virtual Vector3 Generate(const HitRec& hrec) const override {
		return _ptr->Random(_origin);
	}


};
