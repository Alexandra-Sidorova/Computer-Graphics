#include "BrightnessFilter.h"
#include "Utils.h"

QColor BrightnessFilter::calculateNewPixelColor(QColor _color, int _x, int _y)
{
	int k = 30;
	return QColor(Clamp(_color.red() + k, 255, 0), Clamp(_color.green() + k, 255, 0),
		Clamp(_color.blue() + k, 255, 0));
};

QImage BrightnessFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
{
	QImage resultImage(_photo);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor photoColor = _photo.pixelColor(x, y);
			QColor newColor = calculateNewPixelColor(photoColor, x, y);
			resultImage.setPixelColor(x, y, newColor);
		}

	return resultImage;
};