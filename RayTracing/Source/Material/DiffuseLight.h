#pragma once
#include "Material.h"
#include "Source/Texture/Texture.h"
class DiffuseLight : public Material
{
public:
private:
	TexturePtr _emit;
public:

	DiffuseLight(const TexturePtr& emit) : _emit(emit) {};
	
	~DiffuseLight();

	virtual bool Scatter(const Ray& ray, const HitRec& hitRec, ScatterRec& scatterRec)const { return false; };

	virtual Vector3 Emitted(const Ray& r, const HitRec& hrec) const {

		//•Ð–Ê‚Ì‚ÝŒõŒ¹‰»‚·‚é
		if (dot(hrec.n,r.Direction()) <0.0f) {
			return _emit->Value(hrec.u, hrec.v, hrec.p);

		}
		else {
			return Vector3(0.0f);
		}
	}
};

