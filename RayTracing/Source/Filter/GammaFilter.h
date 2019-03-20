#pragma once
#include "ImageFilter.h"

class GammaFilter : public ImageFilter
{
public:
private:
	float _factor;

public:
	GammaFilter();
	GammaFilter(float factor) : _factor(factor) {};

	virtual ~GammaFilter();
	virtual Vector3 filter(const Vector3& c) const override {
		return linear_to_gamma(c, _factor);
	}
};

