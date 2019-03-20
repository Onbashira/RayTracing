#include "Box.h"



Box::Box(const Vector3 & p0, const Vector3 & p1, const MaterialPtr & m) :
	_p0(p0), _p1(p1), _list(std::make_unique<ShapeList>())
{

	ShapeList* l = new ShapeList();
	l->Add(std::make_shared<Rect>(
		p0.getX(), p1.getX(), p0.getY(), p1.getY(), p1.getZ(), Rect::XY, m));
	l->Add(std::make_shared<FlipNormals>(std::make_shared<Rect>(
		p0.getX(), p1.getX(), p0.getY(), p1.getY(), p0.getZ(), Rect::XY, m)));
	l->Add(std::make_shared<Rect>(
		p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p1.getY(), Rect::XZ, m));
	l->Add(std::make_shared<FlipNormals>(std::make_shared<Rect>(
		p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p0.getY(), Rect::XZ, m)));
	l->Add(std::make_shared<Rect>(
		p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p1.getX(), Rect::YZ, m));
	l->Add(std::make_shared<FlipNormals>(std::make_shared<Rect>(
		p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p0.getX(), Rect::YZ, m)));
	_list.reset(l);
}

Box::~Box()
{
}

bool Box::Hit(const Ray & ray, float t0, float t1, HitRec & hrec) const
{
	return _list->Hit(ray,t0,t1,hrec);
}
