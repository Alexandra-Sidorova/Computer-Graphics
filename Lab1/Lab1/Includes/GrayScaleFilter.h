#ifndef _GRAYSCALEFILTER_H_
#define _GRAYSCALEFILTER_H_

#include "Filter.h"

class GrayScaleFilter : public Filter
{
public:
	GrayScaleFilter() {};
	~GrayScaleFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
	QColor calculateNewPixelColor(QImage, int, int);
};

#endif
