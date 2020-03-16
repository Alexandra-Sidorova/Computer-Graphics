#include "SepiaFilter.h"
#include "Intensity.h"
#include "Utils.h"

QColor SepiaFilter::calculateNewPixelColor(QImage _photo, int _x, int _y)
{
	int k = 20;
	Intensity intensity(_photo.pixelColor(_x, _y), _x, _y);
	return QColor(Clamp(intensity.value + 2 * k, 255, 0), Clamp(intensity.value + 0.5 * k, 255, 0), 
		Clamp(intensity.value - k, 255, 0));
};

QImage SepiaFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
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