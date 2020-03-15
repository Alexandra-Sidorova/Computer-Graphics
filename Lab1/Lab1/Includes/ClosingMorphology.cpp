#include "ClosingMorphology.h"
#include "DilationMorphology.h"
#include "ErosionMorphology.h"

QImage ClosingMorphology::calculateNewImagePixMap(const QImage& _photo, const Mask& _mask)
{
	DilationMorphology* dilation = new DilationMorphology();
	QImage dilationImage = dilation->calculateNewImagePixMap(_photo, _mask);
	ErosionMorphology* erosion = new ErosionMorphology();
	return erosion->calculateNewImagePixMap(dilationImage, _mask);
};