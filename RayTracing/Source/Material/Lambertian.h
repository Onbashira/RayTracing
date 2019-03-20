#pragma once
#include "Material.h"
#include "Source/Texture/Texture.h"
#include "Source/Pdf/CosinePdf.h"
class Lambertian : public Material
{
public:
private:
	TexturePtr _albedo;

	CosinePdf _pdf;
public:

	Lambertian();

	Lambertian(const TexturePtr& albedo) : _albedo(albedo) {};

	virtual ~Lambertian();

	virtual bool Scatter(const Ray& ray, const HitRec& hrec, ScatterRec& srec)const override;
	
	virtual float ScatteringPdf(const Ray& ray, const HitRec& hrec) const override;


};

