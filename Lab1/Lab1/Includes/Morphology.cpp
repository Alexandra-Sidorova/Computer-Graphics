#include "Morphology.h"
#include "Utils.h"


QImage Morphology::Closing(const QImage& _photo)
{
	return Erosion(Dilation(_photo));
};

QImage Morphology::TopHat(const QImage& _photo)
{
	QImage result(_photo);
	QImage openingPhoto = Opening(_photo);

	for(int x = 0; x < _photo.width(); x++)
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