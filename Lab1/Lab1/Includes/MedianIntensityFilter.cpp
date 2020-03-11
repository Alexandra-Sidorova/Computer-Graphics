#include "MedianIntensityFilter.h"
#include "Intensity.h"
#include "Utils.h"

QColor MedianIntensityFilter::calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius)
{
	int size = 2 * _radius + 1;
	Intensity* intens = new Intensity[size * size];
	int idx, idy;
	int index = 0;

	for (int i = -_radius; i <= _radius; i++)
		for (int j = -_radius; j <= _radius; j++)
		{
			idx = Clamp<int>(_x + i, _photo.width() - 1, 0);
			idy = Clamp<int>(_y + i, _photo.height() - 1, 0);
			Intensity tmp(_photo.pixelColor(idx, idy), idx, idy);
			intens[index++] = tmp;
		}

	SortIntensity<float>(intens, index);
	idx = intens[size * size / 2].x;
	idy = intens[size * size / 2].y;

	return _photo.pixelColor(idx, idy);
};


QImage MedianIntensityFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
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