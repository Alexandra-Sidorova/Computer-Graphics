#ifndef _DILATIONMORPHOLOGY_H_
#define _DILATIONMORPHOLOGY_H_

#include "Morphology.h"
#include "Mask.h"

class DilationMorphology : public Morphology
{
public:
	DilationMorphology() {};
	~DilationMorphology() {};

	QImage calculateNewImagePixMap(const QImage& _photo, const Mask& _mask);
};

#endif