#ifndef _MIRRORFILTER_H_
#define _MIRRORFILTER_H_

#include "Filter.h"

class MirrorFilter : public Filter
{
public:
	MirrorFilter() {};
	~MirrorFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
	QColor calculateNewPixelColor(QImage, int, int, int);
};

#endif
