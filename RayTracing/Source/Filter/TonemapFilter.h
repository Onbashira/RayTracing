#pragma once
#include "ImageFilter.h"

class TonemapFilter : public ImageFilter
{
public:
private:

public:
	TonemapFilter();
	virtual ~TonemapFilter();
	virtual Vector3 filter(const Vector3& c) const override {
		return minPerElem(maxPerElem(c, Vector3(0.f)), Vector3(1.f));;
	}
};

