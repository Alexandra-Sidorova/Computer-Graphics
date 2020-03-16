#ifndef _SEPIAFILTER_H_
#define _SEPIAFILTER_H_

#include "Filter.h"

class SepiaFilter : public Filter
{
public:
	SepiaFilter() {};
	~SepiaFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
	QColor calculateNewPixelColor(QImage, int, int);
};

#endif