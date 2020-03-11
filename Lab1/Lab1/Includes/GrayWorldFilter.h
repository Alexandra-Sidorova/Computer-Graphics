#ifndef _GRAYWORLDFILTER_H_
#define _GRAYWORLDFILTER_H_

#include "Filter.h"

class GrayWorldFilter : public Filter
{
public:
	GrayWorldFilter() {};
	~GrayWorldFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	QColor calculateNewPixelColor(QImage _photo, int _x, int _y, int _avg, QColor _avgRGB);
};

#endif