#ifndef _EROSIONMORPHOLOGY_H_
#define _EROSIONMORPHOLOGY_H_

#include "Morphology.h"

class ErosionMorphology : public Morphology
{
public:
	ErosionMorphology() {};
	~ErosionMorphology() {};

	QImage calculateNewImagePixMap(const QImage & _photo, const Mask & _mask);
};

#endif