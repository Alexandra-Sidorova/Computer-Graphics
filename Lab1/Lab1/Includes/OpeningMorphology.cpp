#include "OpeningMorphology.h"
#include "DilationMorphology.h"
#include "ErosionMorphology.h"

QImage OpeningMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	ErosionMorphology* erosion = new ErosionMorphology();
	QImage erosionImage = erosion->calculateNewImagePixMap(_photo, _mask);
	DilationMorphology* dilation = new DilationMorphology();
	return dilation->calculateNewImagePixMap(erosionImage, _mask);
};