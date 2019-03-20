#pragma once

#include "Source/Filter/ImageFilter.h"
#include <memory>
#include <string>
#include <vector>

class Image
{
public:
	struct RGB {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
private:
	unsigned int _width;
	unsigned int _height;
	std::unique_ptr<RGB[]> _pixels;
	std::vector<std::unique_ptr<ImageFilter>> _filters;

public:

	Image();

	Image(int w, int h);

	~Image() {};

	int Width() const { return _width; }
	int Height() const { return _height; }
	void* Pixels() const { return _pixels.get(); }

	void Write(int x, int y, float r, float g, float b);

	void OutputImage(const std::string& filename);

};

