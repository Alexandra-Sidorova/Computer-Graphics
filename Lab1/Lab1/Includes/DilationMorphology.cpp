#include "DilationMorphology.h"
#include "Utils.h"

QImage DilationMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	QImage result(_photo);

	for (int x = 0; x < _photo.width(); x++)
	{
		for (int y = 0; y < _photo.height(); y++)
		{
			int maxR = 0;
			int maxG = 0;
			int maxB = 0;

			for (int i = -_mask.GetWidth() / 2; i < _mask.GetWidth() / 2; i++)
				for (int j = -_mask.GetHeight() / 2; j < _mask.GetHeight() / 2; j++)
				{
					QColor color = _photo.pixelColor(Clamp<int>(x + i, _photo.width() - 1, 0),
						Clamp<int>(y + j, _photo.height() - 1, 0));

					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.red() > maxR))
						maxR = color.red();
					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.green() > maxG))
						maxG = color.green();
					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.blue() > maxB))
						maxB = color.blue();
				}

			result.setPixelColor(x, y, QColor(maxR, maxG, maxB));
		}
	}

	return result;
};