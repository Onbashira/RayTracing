#pragma once
#include "Material.h"
#include "Source/Texture/Texture.h"
class Metal : public Material
{
public:

private:

	TexturePtr _albedo;
	float _raoughness;
public:
	Metal();

	Metal(const TexturePtr& albedo , float raoughness) : _albedo(albedo), _raoughness(raoughness) {};

	virtual ~Metal();

	virtual bool Scatter(const Ray& ray, const HitRec& hrec, ScatterRec& srec)const override;

	virtual Vector3 Emitted(const Ray& r, const HitRec& hrec) const { return Vector3(0); }

	virtual float ScatteringPdf(const Ray& r, const HitRec& hrec) const { return 0.0f; };

};

