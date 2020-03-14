#include "HistogramLinearStretchFilter.h"
#include "Utils.h"

QColor HistogramLinearStretchFilter::calculateNewPixelColor(QImage _photo, int _x, int _y)
{
	QColor color = _photo.pixelColor(_x, _y);

	return QColor(
		Clamp((int)(((color.red() - minR) * (255 - 0)) / (maxR - minR)), 255, 0),
		Clamp((int)(((color.green() - minG) * (255 - 0)) / (maxG - minG)), 255, 0),
		Clamp((int)(((color.blue() - minB) * (255 - 0)) / (maxB - minB)), 255, 0));
};

QImage HistogramLinearStretchFilter::calculateNewImagePixMap(const QImage& _photo, int _mRadius)
{
	QImage resultImage(_photo);

	minR = maxR = _photo.pixelColor(0, 0).red();
	minG = maxG = _photo.pixelColor(0, 0).green();
	minB = maxB = _photo.pixelColor(0, 0).blue();

	for (int i = 0; i < _photo.width(); i++)
	{
		for (int j = 0; j < _photo.height(); j++)
		{
			QColor curColor = _photo.pixelColor(i, j);

			if (curColor.red() < minR)
				minR = curColor.red();
			if (curColor.red() > maxR)
				maxR = curColor.red();

			if (curColor.green() < minG)
				minG = curColor.green();
			if (curColor.green() > maxG)
				maxG = curColor.green();

			if (curColor.blue() < minB)
				minB = curColor.blue();
			if (curColor.blue() > maxB)
				maxB = curColor.blue();
		}
	}

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor newColor = calculateNewPixelColor(_photo, x, y);
			resultImage.setPixelColor(x, y, newColor);
		}

	return resultImage;
};