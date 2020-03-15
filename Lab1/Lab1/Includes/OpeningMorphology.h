#ifndef _OPENINGMORPHOLOGY_H_
#define _OPENINGMORPHOLOGY_H_

#include "Morphology.h"

class OpeningMorphology : public Morphology
{
public:
	OpeningMorphology() {};
	~OpeningMorphology() {};

	QImage calculateNewImagePixMap(const QImage& _photo, const Mask& _mask);
};

#endif
