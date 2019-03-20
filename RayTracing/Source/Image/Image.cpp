#include "Image.h"
#include "Source/Filter/GammaFilter.h"
#include "Source/Filter/TonemapFilter.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "thirdParty/stb/stb_image.h"
#include "thirdParty/stb/stb_image_write.h"

Image::Image() :
	_width(0), _height(0), _pixels(nullptr)
{

}
Image::Image(int w, int h) :
	_width(w), _height(h)
{
	_width = w;
	_height = h;
	_pixels.reset(new RGB[_width*_height]);
	_filters.push_back(std::make_unique<GammaFilter>(GAMMA_FACTOR));
	_filters.push_back(std::make_unique<TonemapFilter>());

};

void Image::Write(int x, int y, float r, float g, float b)
{	
	Vector3 c(r, g, b);

	for (auto& f : _filters) {
		c = f->filter(c);
	}
	int index = _width * y + x;

	_pixels[index].r = static_cast<unsigned char>(c.getX()*255.99f);
	_pixels[index].g = static_cast<unsigned char>(c.getY()*255.99f);
	_pixels[index].b = static_cast<unsigned char>(c.getZ()*255.99f);
}

void Image::OutputImage(const std::string & filename)
{

	stbi_write_bmp("render.bmp", _width, _height, sizeof(Image::RGB), reinterpret_cast<void*>(_pixels.get()));

}
