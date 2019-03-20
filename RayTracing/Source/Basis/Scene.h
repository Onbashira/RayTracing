#pragma once
#include "Source/Utility/MathUtil.h"
#include "Source/Basis/Ray.h"
#include "Source/Shape/Shape.h"
#include "Source/Image/Image.h"
#include "Source/Basis/Camera.h"
#include <memory>
#include <iostream>

#define NUM_THREAD 8
#define THRESHOLD 0.001f
#define MAX_DEPTH 100

class Scene 
{
public:
private:
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Image> _image;
	std::unique_ptr<Shape> _world;
	std::unique_ptr<Shape> _light;

	Vector3 _backColor;
	int _samples;
public:

	Scene(int width, int height, int samples);
	~Scene();

	void Build();
	void BuildConelBox();
	Vector3 Color(const Ray& r , const Shape* world, const Shape* light, int depth);
	Vector3 BackgroundSky(const Vector3& d) const;
	Vector3 Background(const Vector3& d) const {
		return _backColor;
	}

	void Render();

};


