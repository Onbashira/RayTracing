#include "ImageTexture.h"
#include "thirdParty/stb/stb_image.h"


ImageTexture::ImageTexture(std::string name)
{
	int nn;
	_texels = stbi_load(name.c_str(), &_width, &_height, &nn, 0);
}

ImageTexture::~ImageTexture()
{
	stbi_image_free(_texels);

}

Vector3 ImageTexture::Value(float u, float v, const Vector3 & p) const
{
	int i = static_cast<int>(u* static_cast<float>(_width));
	int j = static_cast<int>((1.0f - v) * static_cast<float>(_height) - 0.001f);
	return Sample(i, j);
}

Vector3 ImageTexture::Sample(int u, int v) const

{
	u = u < 0 ? 0 : u >= _width ? _width - 1 : u;
	v = v < 0 ? 0 : v >= _height ? _height - 1 : v;
	return Vector3(
		int(_texels[3 * u + 3 * _width * v]) / 255.0f,
		int(_texels[3 * u + 3 * _width * v + 1]) / 255.0f,
		int(_texels[3 * u + 3 * _width * v + 2]) / 255.0f);
}
