#ifndef _GAUSSIANBLURFILTER_H_
#define _GAUSSIANBLURFILTER_H_

#include "MatrixFilter.h"

class GaussianBlurFilter : public MatrixFilter
{
public:
	GaussianBlurFilter();
	~GaussianBlurFilter() {};

	void createGaussianKernel(int, int);
};

#endif