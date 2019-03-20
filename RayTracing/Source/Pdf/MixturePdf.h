#pragma once
#include "Source/Pdf/Pdf.h"
class MixturePdf : public Pdf
{
private:
	const Pdf* _pdfs[2];

public:

	MixturePdf(const Pdf* p0, const Pdf* p1) { _pdfs[0] = p0; _pdfs[1] = p1; }
	
	~MixturePdf() {};

	virtual float Value(const HitRec& hrec, const Vector3& direction) const override {
		float pdf0_value = _pdfs[0]->Value(hrec, direction);
		float pdf1_value = _pdfs[1]->Value(hrec, direction);
		return 0.5f*pdf0_value + 0.5f*pdf1_value;
	}

	virtual Vector3 Generate(const HitRec& hrec) const override {
		if (drand48() < 0.5f) {
			return _pdfs[0]->Generate(hrec);
		}
		else {
			return _pdfs[1]->Generate(hrec);
		}
	}
};

