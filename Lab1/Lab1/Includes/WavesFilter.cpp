#define _USE_MATH_DEFINES

#include "WavesFilter.h"
#include "Utils.h"

#include <cmath>

WavesFilter::WavesFilter(bool _horizontal, int _length)
{
	horizontal = _horizontal;
	length = _length;
};

QImage WavesFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
{
	QImage resultImage(_photo);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor newColor = calculateNewPixelColor(_photo, x, y, _radius);
			resultImage.setPixelColor(x, y, newColor);
		}

	return resultImage;
};

QColor WavesFilter::calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius)
{
	int idx;
	if (horizontal)
		idx = Clamp<int>(_x + (int)(length * sin(2 * M_PI * _y / 60)), _photo.width() - 1, 0);
	else
		idx = Clamp<int>(_x + (int)(length * sin(2 * M_PI * _x / 30)), _photo.width() - 1, 0);

	int idy = Clamp(_y, _photo.height() - 1, 0);

	return _photo.pixelColor(idx, idy);
};