#include "MirrorFilter.h"
#include "Utils.h"

QImage MirrorFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
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

QColor MirrorFilter::calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius)
{
	int idx = Clamp<int>(_x + (int)((rand() / (double)(RAND_MAX) - 0.5) * 10), _photo.width() - 1, 0);
	int idy = Clamp<int>(_y + (int)((rand() / (double)(RAND_MAX) - 0.5) * 10), _photo.height() - 1, 0);

	return _photo.pixelColor(idx, idy);
};
