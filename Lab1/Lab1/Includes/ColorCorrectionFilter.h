#ifndef _COLORCORRECTIONFILTER_H_
#define _COLORCORRECTIONFILTER_H_

#include "Filter.h"

class ColorCorrectionFilter : public Filter
{
protected:
	QColor coeff; // R = R * coeff / source
	QColor source;

public:
	ColorCorrectionFilter() {};
	~ColorCorrectionFilter() {};

	QColor calculateNewPixelColor(QImage _photo, int _x, int _y);
	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	virtual void SetCoeffAndSource(QImage _photo) = 0;
};

#endif