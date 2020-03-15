#include "ErosionMorphology.h"

QImage ErosionMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	QImage result(_photo);

	for (int x = _mask.GetWidth() / 2; x < (_photo.width() - _mask.GetWidth() / 2); x++)
	{
		for (int y = _mask.GetHeight() / 2; y < (_photo.height() - _mask.GetHeight() / 2); y++)
		{
			int minR = 255;
			int minG = 255;
			int minB = 255;

			for (int i = -_mask.GetWidth() / 2; i < _mask.GetWidth() / 2; i++)
				for (int j = -_mask.GetHeight() / 2; j < _mask.GetHeight() / 2; j++)
				{
					QColor color = _photo.pixelColor(x + i, y + j);

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