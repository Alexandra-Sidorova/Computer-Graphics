#ifndef _MATRIXFILTER_H_
#define _MATRIXFILTER_H_

#include "Filter.h"

class MatrixFilter : public Filter
{
public:
	float* vector;
	int mRadius;

	MatrixFilter(int _radius = 1) : mRadius(_radius) {};
	~MatrixFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
	QColor calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius);
};
#endif