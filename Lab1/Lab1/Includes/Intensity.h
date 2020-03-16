#ifndef _INTENSITY_H_
#define _INTENSITY_H_

#include <qimage>

class Intensity
{
public:
	int x;
	int y;
	int value;

	Intensity() {};
	Intensity(const QColor, int, int);
	~Intensity() {};

	const Intensity& operator=(const Intensity&);
};

#endif