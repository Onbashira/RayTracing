#pragma once
#include "Source/Utility/MathUtil.h"
class Texture
{
public:

public:
	
	Texture();
	
	virtual ~Texture();

	virtual Vector3 Value(float u, float v, const Vector3& p) const = 0;
};
class Texture;
typedef std::shared_ptr<Texture> TexturePtr;
