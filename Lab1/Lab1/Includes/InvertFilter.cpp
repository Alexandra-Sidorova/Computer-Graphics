#include "InvertFilter.h"

QImage InvertFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
{
	QImage resultImage(_photo);

	for(int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor photoColor = _photo.pixelColor(x, y);
			photoColor.setRgb(255 - photoColor.red(), 255 - photoColor.green(),
							  255 - photoColor.blue());
			resultImage.setPixelColor(x, y, photoColor);
		}

	return resultImage;
};