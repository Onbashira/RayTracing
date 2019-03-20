#pragma once
#include "Texture.h"
#include <string>
class ImageTexture :
	public Texture
{
public :
	int _width;
	int _height;
	unsigned char* _texels;
public:

	ImageTexture(std::string name);
	
	virtual ~ImageTexture();

	virtual Vector3 Value(float u, float v, const Vector3& p) const;

	Vector3 Sample(int u, int v) const;
};

