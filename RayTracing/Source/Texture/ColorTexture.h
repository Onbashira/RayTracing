#pragma once
#include "Texture.h"

class ColorTexture : public Texture
{

private:
		Vector3 _color;
public:
	ColorTexture();
	ColorTexture(const Vector3 color) : _color(color) {};
	virtual ~ColorTexture();
	virtual Vector3 Value(float u, float v, const Vector3& p) const override {
		return _color;
	}
};

