#include "ShapeList.h"



ShapeList::ShapeList()
{
}


ShapeList::~ShapeList()
{
}

void ShapeList::Add(const ShapePtr & shape)
{
	_list.push_back(shape);
}

bool ShapeList::Hit(const Ray & r, float t0, float t1, HitRec & hrec) const
{
	HitRec temp_rec;
	bool hit_anything = false;
	float closest_so_far = t1;
	for (auto& p : _list) {
		if (p->Hit(r, t0, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			hrec = temp_rec;
		}
	}
	return hit_anything;
}

float ShapeList::PdfValue(const Vector3 & o, const Vector3 & v) const
{
	float weight = 1.0f / _list.size();
	float sum = 0;
	for (auto& p : _list) {
		sum += weight * p->PdfValue(o, v);
	}
	return sum;
}

Vector3 ShapeList::Random(const Vector3 & o) const
{
	size_t n = _list.size();
	size_t index = size_t(drand48() * n);
	if (n > 0 && index >= n) {
		index = n - 1;
	}
	return _list[index]->Random(o);
}
