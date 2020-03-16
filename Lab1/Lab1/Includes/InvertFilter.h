#ifndef _INVERTFILTER_H_
#define _INVERTFILTER_H_

#include "Filter.h"

class InvertFilter : public Filter
{
public:
	InvertFilter() {};
	~InvertFilter() {};

	QImage calculateNewImagePixMap(const QImage&, int);
};

#endif