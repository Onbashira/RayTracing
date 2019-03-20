#pragma once
#include "Pdf.h"
class CosinePdf :
	public Pdf
{
public:
	CosinePdf();
	~CosinePdf();

	virtual float Value(const HitRec& hrec, const Vector3& dir)const;

	virtual Vector3 Generate(const HitRec& hrec)const;
};

