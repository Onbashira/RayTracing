#include "Lambertian.h"
#include "Source/Utility/MathUtil.h"
#include "Source/Pdf/CosinePdf.h"

Lambertian::Lambertian()
{
}


Lambertian::~Lambertian()
{
}

bool Lambertian::Scatter(const Ray & ray, const HitRec & hrec, ScatterRec & srec) const
{
	//::ONB onb;
	////�@���������̐��K���s���
	//onb.build_from_w(hrec.n);
	//Vector3 direction = onb.local(random_cosine_direction());

	//srec.ray = Ray(hrec.p, direction);
	srec.albedo = _albedo->Value(hrec.u,hrec.v,hrec.p);
	srec.pdfValue = &_pdf;
	srec.isSpecular = false;

	return true;
}

float Lambertian::ScatteringPdf(const Ray & ray, const HitRec & hrec) const
{
	//���K�������o�[�g
	return (Max(0.0f,dot(hrec.n , normalize(ray.Direction()))) / F_PI);
}
