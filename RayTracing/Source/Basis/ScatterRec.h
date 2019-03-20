#pragma once
#include "Source/Basis/Ray.h"
#include "Source/Pdf/Pdf.h"
struct ScatterRec
{
public:
	Ray ray;
	Vector3 albedo;
	const Pdf* pdfValue;
	bool isSpecular;
public:
	ScatterRec();
	virtual ~ScatterRec();
};

