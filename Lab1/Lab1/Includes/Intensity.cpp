#include "Intensity.h"

Intensity::Intensity(const QColor _color, int _x, int _y) : x(_x), y(_y)
{
	value = 0.36 * _color.red() + 0.53 * _color.green() + 0.11 * _color.blue();
};

const Intensity& Intensity::operator=(const Intensity& _copy)
{
	if (this == &_copy)
		return *this;

	value = _copy.value;
	x = _copy.x;
	y = _copy.y;

	return *this;
};