#include "ErosionMorphology.h"
#include "Utils.h"

QImage ErosionMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	QImage result(_photo);

	for (int x = 0; x < _photo.width(); x++)
	{
		for (int y = 0; y < _photo.height(); y++)
		{
			int minR = 255;
			int minG = 255;
			int minB = 255;

			for (int i = -_mask.GetWidth() / 2; i < _mask.GetWidth() / 2; i++)
				for (int j = -_mask.GetHeight() / 2; j < _mask.GetHeight() / 2; j++)
				{
					QColor color = _photo.pixelColor(Clamp<int>(x + i, _photo.width() - 1, 0),
						Clamp<int>(y + j, _photo.height() - 1, 0));

					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.red() < minR))
						minR = color.red();
					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.green() < minG))
						minG = color.green();
					if (_mask.GetMask()[i * _mask.GetWidth() + j] && (color.blue() < minB))
						minB = color.blue();
				}

			result.setPixelColor(x, y, QColor(minR, minG, minB));
		}
	}

	return result;
};