#ifndef _WAVESFILTER_H_
#define _WAVESFILTER_H_

#include "Filter.h"

class WavesFilter : public Filter
{
public:
	bool horizontal;
	int length;

	WavesFilter(bool _horizontal = 1, int _length = 20);
	~WavesFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	QColor calculateNewPixelColor(QImage _photo, int _x, int _y, int _mRadius);
};

#endif