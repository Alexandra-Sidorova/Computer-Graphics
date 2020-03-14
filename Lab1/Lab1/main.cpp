#include <QImage>
#include <string>

#include "Includes/InvertFilter.h"
#include "Includes/BlurFilter.h"
#include "Includes/GaussianBlurFilter.h"
#include "Includes/WavesFilter.h"
#include "Includes/MirrorFilter.h"
#include "Includes/SharpnessFilter.h"
#include "Includes/MotionBlurFilter.h"
#include "Includes/MedianIntensityFilter.h"
#include "Includes/GrayScaleFilter.h"
#include "Includes/SepiaFilter.h"
#include "Includes/BrightnessFilter.h"
#include "Includes/SharpnessFilter_2.h"
#include "Includes/SobelYFilter.h"
#include "Includes/SobelXFilter.h"
#include "Includes/GrayWorldFilter.h"
#include "Includes/HistogramLinearStretchFilter.h"

using namespace std;

void main(int argc, char *argv[])
{
	string s;
	QImage photo;

	for (int i = 0; i < argc; i++)
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
			s = argv[i + 1];

	photo.load(QString(s.c_str()));
	photo.save("Resources/Starting.PNG");

	InvertFilter* invert = new InvertFilter();
	QImage invertImage = invert->calculateNewImagePixMap(photo, 0);
	invertImage.save("Resources/Invert.PNG");

	BlurFilter* blur = new BlurFilter();
	QImage blurImage = blur->calculateNewImagePixMap(photo, 1);
	blurImage.save("Resources/Blur.PNG");

	GaussianBlurFilter* gaussianBlur = new GaussianBlurFilter();
	QImage gaussianBlurImage = gaussianBlur->calculateNewImagePixMap(photo, 3);
	gaussianBlurImage.save("Resources/GaussianBlur.PNG");

	WavesFilter* wavesHorizontal = new WavesFilter();
	QImage wavesHorizontalImage = wavesHorizontal->calculateNewImagePixMap(photo, 0);
	wavesHorizontalImage.save("Resources/WavesHorizontal.PNG");

	WavesFilter* wavesVertical = new WavesFilter(0);
	QImage wavesVerticalImage = wavesVertical->calculateNewImagePixMap(photo, 0);
	wavesVerticalImage.save("Resources/WavesVertical.PNG");

	MirrorFilter* mirror = new MirrorFilter();
	QImage mirrorImage = mirror->calculateNewImagePixMap(photo, 0);
	mirrorImage.save("Resources/Mirror.PNG");

	SharpnessFilter* sharpness = new SharpnessFilter();
	QImage sharpnessImage = sharpness->calculateNewImagePixMap(photo, 1);
	sharpnessImage.save("Resources/Sharpness.PNG");

	SharpnessFilter_2* sharpness_2 = new SharpnessFilter_2();
	QImage sharpnessImage_2 = sharpness_2->calculateNewImagePixMap(photo, 1);
	sharpnessImage_2.save("Resources/Sharpness_2.PNG");

	MotionBlurFilter* motionBlur = new MotionBlurFilter();
	QImage MotionBlurImage = motionBlur->calculateNewImagePixMap(photo, 1);
	MotionBlurImage.save("Resources/MotionBlur.PNG");

	MedianIntensityFilter* medianIntensity = new MedianIntensityFilter();
	QImage medianIntensityImage = medianIntensity->calculateNewImagePixMap(photo, 1);
	medianIntensityImage.save("Resources/MedianIntensity.PNG");

	GrayScaleFilter* grayScale = new GrayScaleFilter();
	QImage grayScaleImage = grayScale->calculateNewImagePixMap(photo, 0);
	grayScaleImage.save("Resources/GrayScale.PNG");

	SepiaFilter* sepia = new SepiaFilter();
	QImage sepiaImage = sepia->calculateNewImagePixMap(photo, 0);
	sepiaImage.save("Resources/Sepia.PNG");

	BrightnessFilter* brightness = new BrightnessFilter();
	QImage brightnessImage = brightness->calculateNewImagePixMap(photo, 0);
	brightnessImage.save("Resources/Brightness.PNG");

	SobelYFilter* sobelY = new SobelYFilter();
	QImage sobelYImage = sobelY->calculateNewImagePixMap(photo, 1);
	sobelYImage.save("Resources/SobelY.PNG");

	SobelXFilter* sobelX = new SobelXFilter();
	QImage sobelXImage = sobelX->calculateNewImagePixMap(photo, 1);
	sobelXImage.save("Resources/SobelX.PNG");

	GrayWorldFilter* grayWorld = new GrayWorldFilter();
	QImage grayWorldImage = grayWorld->calculateNewImagePixMap(photo, 0);
	grayWorldImage.save("Resources/GrayWorld.PNG");

	HistogramLinearStretchFilter* histogramLinearScretch = new HistogramLinearStretchFilter();
	QImage histogramLinearScretchImage = histogramLinearScretch->calculateNewImagePixMap(photo, 0);
	histogramLinearScretchImage.save("Resources/HistogramLinearStretchFilter.PNG");
}
