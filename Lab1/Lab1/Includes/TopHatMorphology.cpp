#include "TopHatMorphology.h"
#include "OpeningMorphology.h"
#include "Utils.h"

QImage TopHatMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	QImage result(_photo);
	OpeningMorphology* opening = new OpeningMorphology();
	QImage openingPhoto = opening->calculateNewImagePixMap(_photo, _mask);

	for (int x = 0; x < _photo.width(); x++)
		for (int y = 0; y < _photo.height(); y++)
		{
			QColor color = result.pixelColor(x, y);
			QColor openColor = openingPhoto.pixelColor(x, y);

			result.setPixelColor(x, y, QColor(Clamp(color.red() - openColor.red(), 255, 0),
				Clamp(color.green() - openColor.green(), 255, 0),
				Clamp(color.blue() - openColor.blue(), 255, 0)));
		}

	return result;
};