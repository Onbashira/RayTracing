#include "CheckerTexture.h"


CheckerTexture::CheckerTexture(const TexturePtr & t0, const TexturePtr & t1, float freq)
	: _odd(t0), _even(t1), _freq(freq) 
{

}

CheckerTexture::~CheckerTexture()
{

}

Vector3 CheckerTexture::Value(float u, float v, const Vector3 & p) const
{
	float sines = sinf(_freq*p.getX()) * sinf(_freq*p.getY()) * sinf(_freq*p.getZ());
	if (sines < 0) {
		return _odd->Value(u, v, p);
	}
	else {
		return _even->Value(u, v, p);
	}
}
