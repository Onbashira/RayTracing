#pragma once
#include "Texture.h"
class CheckerTexture : public Texture
{
private:
	TexturePtr _odd;

	TexturePtr _even;

	float _freq;

public:
	CheckerTexture(const TexturePtr& t0, const TexturePtr& t1, float freq);
	virtual ~CheckerTexture();
	virtual Vector3 Value(float u, float v, const Vector3& p) const;

};

