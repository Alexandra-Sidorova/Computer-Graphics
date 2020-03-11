#ifndef _BRIGHTNESSFILTER_H_
#define _BRIGHTNESSFILTER_H_

#include "Filter.h"

class BrightnessFilter: public Filter
{
public:
	BrightnessFilter() {};
	~BrightnessFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
	QColor calculateNewPixelColor(QColor, int, int);
};

#endif