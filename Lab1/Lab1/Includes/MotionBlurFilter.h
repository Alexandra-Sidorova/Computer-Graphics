#ifndef _MOTIONBLUR_H_
#define _MOTIONBLUR_H_

#include "MatrixFilter.h"

class MotionBlurFilter : public MatrixFilter
{
public:
	MotionBlurFilter();
	~MotionBlurFilter() {};
};
#endif