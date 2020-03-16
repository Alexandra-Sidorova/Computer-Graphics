#include "MatrixFilter.h"
#include "Utils.h"

MatrixFilter::~MatrixFilter()
{
	mRadius = 0;
	delete[] vector;
};
//-------------------------------------------------

QColor MatrixFilter::calculateNewPixelColor(QImage _photo, int _x, int _y, int _radius)
{
	float returnR = 0;
	float returnG = 0;
	float returnB = 0;
	int size = 2 * _radius + 1;

	for(int i = -_radius; i <= _radius; i++)
		for (int j = -_radius; j <= _radius; j++)
		{
			int idx = (i + _radius) * size + (j + _radius);

			QColor color = _photo.pixelColor(Clamp<int>(_x + i, _photo.width() - 1, 0),
				                       Clamp<int> (_y + j, _photo.height() - 1, 0));

			returnR += color.red() * vector[idx];
			returnG += color.green() * vector[idx];
			returnB += color.blue() * vector[idx];
		}

	return QColor(Clamp(returnR, 255, 0), Clamp(returnG, 255, 0), Clamp(returnB, 255, 0));
};

QImage MatrixFilter::calculateNewImagePixMap(const QImage& _photo, int _radius)
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