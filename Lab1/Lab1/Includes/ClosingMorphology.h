#ifndef _CLOSINGMORPHOLOGY_H_
#define _CLOSINGMORPHOLOGY_H_

#include "Morphology.h"

class ClosingMorphology: public Morphology
{
public:
	ClosingMorphology() {};
	~ClosingMorphology() {};

	QImage calculateNewImagePixMap(const QImage& _photo, const Mask& _mask);
};

#endif
