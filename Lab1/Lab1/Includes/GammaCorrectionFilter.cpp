#include "GammaCorrectionFilter.h"
#include "Utils.h"

#include <cmath>

QImage GammaCorrectionFilter::calculateNewImagePixMap(const QImage& _photo, int _mRadius)
{
	gamma = 1.2;
	c = 1;

	QImage result(_photo);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor color = _photo.pixelColor(x, y);
			result.setPixelColor(x, y, QColor(Clamp(c * pow(color.red(), gamma), 255, 0), Clamp(c * pow(color.green(), gamma), 255, 0),
				Clamp(c * pow(color.blue(), gamma), 255, 0)));
		}

	return result;
}