#ifndef _FILTER_H_
#define _FILTER_H_

#include <QImage>

class Filter
{
public:
	Filter() {};
	~Filter() {};

	virtual QImage calculateNewImagePixMap(const QImage& _photo, int _mRadius) = 0;
};

#endif