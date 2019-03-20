#pragma once
#include "Source/Utility/MathUtil.h"
class ImageFilter
{
public:

	ImageFilter();

	virtual ~ImageFilter();

	virtual Vector3 filter(const Vector3& c)const = 0;

};

