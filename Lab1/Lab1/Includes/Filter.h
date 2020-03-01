#ifndef _FILTER_H_
#define _FILTER_H_

#include <QImage>

class Filter
{
public:
	Filter() {};
	~Filter() {};

	virtual QImage calculateNewImagePixMap(const QImage&, int) = 0;
};

#endif