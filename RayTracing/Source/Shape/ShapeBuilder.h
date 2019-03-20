#pragma once
#include "Source/Shape/Shape.h"
#include "Source/Shape/Sphere.h"
#include "Source/Shape/Rect.h"
#include "Source/Shape/ShapeList.h"
#include "Source/Shape/Rect.h"
#include "Source/Shape/FlipNormals.h"
#include "Source/Shape/Box.h"
#include "Source/Shape/Rotate.h"
#include "Source/Shape/Translate.h"

class ShapeBuilder {
public:
	ShapeBuilder() {}
	ShapeBuilder(const ShapePtr& sp)
		: m_ptr(sp) {
	}

	ShapeBuilder& reset(const ShapePtr& sp) {
		m_ptr = sp;
		return *this;
	}

	ShapeBuilder& sphere(const Vector3& c, float r, const MaterialPtr& m) {
		m_ptr = std::make_shared<Sphere>(c, r, m);
		return *this;
	}

	ShapeBuilder& rect(float x0, float x1, float y0, float y1, float k, Rect::AxisType axis, const MaterialPtr& m) {
		m_ptr = std::make_shared<Rect>(x0, x1, y0, y1, k, axis, m);
		return *this;
	}
	ShapeBuilder& rectXY(float x0, float x1, float y0, float y1, float k, const MaterialPtr& m) {
		m_ptr = std::make_shared<Rect>(x0, x1, y0, y1, k, Rect::XY, m);
		return *this;
	}
	ShapeBuilder& rectXZ(float x0, float x1, float y0, float y1, float k, const MaterialPtr& m) {
		m_ptr = std::make_shared<Rect>(x0, x1, y0, y1, k, Rect::XZ, m);
		return *this;
	}
	ShapeBuilder& rectYZ(float x0, float x1, float y0, float y1, float k, const MaterialPtr& m) {
		m_ptr = std::make_shared<Rect>(x0, x1, y0, y1, k, Rect::YZ, m);
		return *this;
	}

	ShapeBuilder& rect(const Vector3& p0, const Vector3& p1, float k, Rect::AxisType axis, const MaterialPtr& m) {
		switch (axis) {
		case Rect::XY:
			m_ptr = std::make_shared<Rect>(
				p0.getX(), p1.getX(), p0.getY(), p1.getY(), k, axis, m);
			break;
		case Rect::XZ:
			m_ptr = std::make_shared<Rect>(
				p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), k, axis, m);
			break;
		case Rect::YZ:
			m_ptr = std::make_shared<Rect>(
				p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), k, axis, m);
			break;
		}
		return *this;
	}
	ShapeBuilder& rectXY(const Vector3& p0, const Vector3& p1, float k, const MaterialPtr& m) {
		return rect(p0, p1, k, Rect::XY, m);
	}
	ShapeBuilder& rectXZ(const Vector3& p0, const Vector3& p1, float k, const MaterialPtr& m) {
		return rect(p0, p1, k, Rect::XZ, m);
	}
	ShapeBuilder& rectYZ(const Vector3& p0, const Vector3& p1, float k, const MaterialPtr& m) {
		return rect(p0, p1, k, Rect::YZ, m);
	}

	ShapeBuilder& box(const Vector3& p0, const Vector3& p1, const MaterialPtr& m) {
		m_ptr = std::make_shared<Box>(p0, p1, m);
		return *this;
	}

	ShapeBuilder& flip() {
		m_ptr = std::make_shared<FlipNormals>(m_ptr);
		return *this;
	}

	ShapeBuilder& translate(const Vector3& t) {
		m_ptr = std::make_shared<Translate>(m_ptr, t);
		return *this;
	}

	ShapeBuilder& rotate(const Vector3& axis, float angle) {
		m_ptr = std::make_shared<Rotate>(m_ptr, axis, angle);
		return *this;
	}

	const ShapePtr& get() const { return m_ptr; }

private:
	ShapePtr m_ptr;
};