#ifndef _MATRIXFILTER_H_
#define _MATRIXFILTER_H_

#include "Filter.h"

class MatrixFilter : public Filter
{
protected:
	float* vector;
	int mRadius;

public:
	MatrixFilter(int _radius = 1) : mRadius(_radius) {};
	~MatrixFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	QColor calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius);
};
#endif