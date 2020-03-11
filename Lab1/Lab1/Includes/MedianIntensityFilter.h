#ifndef _MEDIANINTENSITYFILTER_H_
#define _MEDIANINTENSITYFILTER_H_

#include "Filter.h"

class MedianIntensityFilter : public Filter
{
public:
	MedianIntensityFilter() {};
	~MedianIntensityFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
	QColor calculateNewPixelColor(QImage, int, int, int);
};
#endif