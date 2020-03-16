#ifndef _HISTOGRAMLINEARSCRETCHFILTER_H_
#define _HISTOGRAMLINEARSCRETCHFILTER_H_

#include "Filter.h"

class HistogramLinearStretchFilter : public Filter
{
private:
	int minR, maxR;
	int minG, maxG;
	int minB, maxB;

public:
	HistogramLinearStretchFilter() {};
	~HistogramLinearStretchFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	QColor calculateNewPixelColor(QImage _photo, int _x, int _y);
};

#endif