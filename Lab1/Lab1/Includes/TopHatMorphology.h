#ifndef _TOPHATMORPHOLOGY_H_
#define _TOPHATMORPHOLOGY_H_

#include "Morphology.h"

class TopHatMorphology : public Morphology
{
public:
	TopHatMorphology() {};
	~TopHatMorphology() {};

	QImage calculateNewImagePixMap(const QImage& _photo, const Mask& _mask);
};

#endif
