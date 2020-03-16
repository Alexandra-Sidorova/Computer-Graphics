#include "GrayScaleFilter.h"
#include "Intensity.h"

QColor GrayScaleFilter::calculateNewPixelColor(QImage _photo, int _x, int _y)
{
	Intensity intensity(_photo.pixelColor(_x, _y), _x, _y);
	return QColor(intensity.value, intensity.value, intensity.value);
};

QImage GrayScaleFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
{
	QImage resultImage(_photo);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor newColor = calculateNewPixelColor(_photo, x, y);
			resultImage.setPixelColor(x, y, newColor);
		}

	return resultImage;
};