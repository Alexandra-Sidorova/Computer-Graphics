#include "GrayWorldFilter.h"
#include "Utils.h"

QColor GrayWorldFilter::calculateNewPixelColor(QImage _photo, int _x, int _y, int _avg, QColor _avgRGB)
{
	int returnR = _photo.pixelColor(_x, _y).red() * _avg;
	int returnG = _photo.pixelColor(_x, _y).green() * _avg;
	int returnB = _photo.pixelColor(_x, _y).blue() * _avg;

	returnR /= _avgRGB.red();
	returnG /= _avgRGB.green();
	returnB /= _avgRGB.blue();

	return QColor(Clamp(returnR, 255, 0), Clamp(returnG, 255, 0), Clamp(returnB, 255, 0));
};

QImage GrayWorldFilter::calculateNewImagePixMap(const QImage& _photo, int _mRadius)
{
	QImage resultImage(_photo);

	int avgR = 0;
	int avgG = 0;
	int avgB = 0;

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			avgR += _photo.pixelColor(x, y).red();
			avgG += _photo.pixelColor(x, y).green();
			avgB += _photo.pixelColor(x, y).blue();
		}

	avgR /= (_photo.width() * _photo.height());
	avgG /= (_photo.width() * _photo.height());
	avgB /= (_photo.width() * _photo.height());

	int avg = (int)((avgR + avgG + avgB) / 3);
	QColor avgRGB(avgR, avgG, avgB);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor newColor = calculateNewPixelColor(_photo, x, y, avg, avgRGB);
			resultImage.setPixelColor(x, y, newColor);
		}

	return resultImage;
};