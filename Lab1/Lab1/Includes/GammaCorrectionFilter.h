#ifndef _GAMMACORRECTIONFILTER_H_
#define _GAMMACORRECTIONFILTER_H_

#include "Filter.h"

class GammaCorrectionFilter : public Filter
{
private:
	float gamma;
	float c;
public:
	GammaCorrectionFilter() {};
	~GammaCorrectionFilter() {};

	QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius);
};

#endif
