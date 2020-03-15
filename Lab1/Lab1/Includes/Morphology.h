#ifndef _MORPHOLOGY_H_
#define _MORPHOLOGY_H_

#include <qimage.h>

#include "Mask.h"

class Morphology
{
public:
	Morphology() {};
	~Morphology() {};

	virtual QImage calculateNewImagePixMap(const QImage& _photo, const Mask& _mask) = 0;

	QImage TopHat(const QImage& _photo);
};

#endif