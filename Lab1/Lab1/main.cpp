#include <QImage>
#include <iostream>
#include <string>

// Filters
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

// Morphology
#include "Includes/DilationMorphology.h"
#include "Includes/ErosionMorphology.h"
#include "Includes/OpeningMorphology.h"
#include "Includes/ClosingMorphology.h"
#include "Includes/TopHatMorphology.h"

using namespace std;

void main(int argc, char *argv[])
{
	string s;
	QImage photo;

	for (int i = 0; i < argc; i++)
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
			s = argv[i + 1];

	cout << "########## TESTING FILTERS PROGRAM ##########" << endl << endl;

	cout << "Photo is loading..." << endl;
	photo.load(QString(s.c_str()));
	photo.save("Resources/Starting.PNG");
	cout << "Photo is saving as Resources/Starting.PNG" << endl << endl;

	/*cout << "Inverting Filter is loading..." << endl;
	InvertFilter* invert = new InvertFilter();
	QImage invertImage = invert->calculateNewImagePixMap(photo, 0);
	invertImage.save("Resources/Invert.PNG");
	cout << "Photo is saving as Resources/Invert.PNG" << endl << endl;

	cout << "Blur Filter is loading..." << endl;
	BlurFilter* blur = new BlurFilter();
	QImage blurImage = blur->calculateNewImagePixMap(photo, 1);
	blurImage.save("Resources/Blur.PNG");
	cout << "Photo is saving as Resources/Blur.PNG" << endl << endl;

	cout << "Gaussian Blur Filter is loading..." << endl;
	GaussianBlurFilter* gaussianBlur = new GaussianBlurFilter();
	QImage gaussianBlurImage = gaussianBlur->calculateNewImagePixMap(photo, 3);
	gaussianBlurImage.save("Resources/GaussianBlur.PNG");
	cout << "Photo is saving as Resources/GaussianBlur.PNG" << endl << endl;

	cout << "Horizontal Waves Filter is loading..." << endl;
	WavesFilter* wavesHorizontal = new WavesFilter();
	QImage wavesHorizontalImage = wavesHorizontal->calculateNewImagePixMap(photo, 0);
	wavesHorizontalImage.save("Resources/WavesHorizontal.PNG");
	cout << "Photo is saving as Resources/WavesHorizontal.PNG" << endl << endl;

	cout << "Vertical Waves Filter is loading..." << endl;
	WavesFilter* wavesVertical = new WavesFilter(0);
	QImage wavesVerticalImage = wavesVertical->calculateNewImagePixMap(photo, 0);
	wavesVerticalImage.save("Resources/WavesVertical.PNG");
	cout << "Photo is saving as Resources/WavesVertical.PNG" << endl << endl;

	cout << "Mirror Filter is loading..." << endl;
	MirrorFilter* mirror = new MirrorFilter();
	QImage mirrorImage = mirror->calculateNewImagePixMap(photo, 0);
	mirrorImage.save("Resources/Mirror.PNG");
	cout << "Photo is saving as Resources/Mirror.PNG" << endl << endl;

	cout << "Sharpness Filter is loading..." << endl;
	SharpnessFilter* sharpness = new SharpnessFilter();
	QImage sharpnessImage = sharpness->calculateNewImagePixMap(photo, 1);
	sharpnessImage.save("Resources/Sharpness.PNG");
	cout << "Photo is saving as Resources/Sharpness.PNG" << endl << endl;

	cout << "Sharpness 2 Filter is loading..." << endl;
	SharpnessFilter_2* sharpness_2 = new SharpnessFilter_2();
	QImage sharpnessImage_2 = sharpness_2->calculateNewImagePixMap(photo, 1);
	sharpnessImage_2.save("Resources/Sharpness_2.PNG");
	cout << "Photo is saving as Resources/Sharpness_2.PNG" << endl << endl;

	cout << "Motion Blur Filter is loading..." << endl;
	MotionBlurFilter* motionBlur = new MotionBlurFilter();
	QImage MotionBlurImage = motionBlur->calculateNewImagePixMap(photo, 1);
	MotionBlurImage.save("Resources/MotionBlur.PNG");
	cout << "Photo is saving as Resources/MotionBlur.PNG" << endl << endl;

	cout << "Intencity Median Filter is loading..." << endl;
	MedianIntensityFilter* medianIntensity = new MedianIntensityFilter();
	QImage medianIntensityImage = medianIntensity->calculateNewImagePixMap(photo, 1);
	medianIntensityImage.save("Resources/MedianIntensity.PNG");
	cout << "Photo is saving as Resources/MedianIntensity.PNG" << endl << endl;
	
	cout << "Gray Scale Filter is loading..." << endl;
	GrayScaleFilter* grayScale = new GrayScaleFilter();
	QImage grayScaleImage = grayScale->calculateNewImagePixMap(photo, 0);
	grayScaleImage.save("Resources/GrayScale.PNG");
	cout << "Photo is saving as Resources/GrayScale.PNG" << endl << endl;

	cout << "Sepia Filter is loading..." << endl;
	SepiaFilter* sepia = new SepiaFilter();
	QImage sepiaImage = sepia->calculateNewImagePixMap(photo, 0);
	sepiaImage.save("Resources/Sepia.PNG");
	cout << "Photo is saving as Resources/Sepia.PNG" << endl << endl;

	cout << "Brightness Filter is loading..." << endl;
	BrightnessFilter* brightness = new BrightnessFilter();
	QImage brightnessImage = brightness->calculateNewImagePixMap(photo, 0);
	brightnessImage.save("Resources/Brightness.PNG");
	cout << "Photo is saving as Resources/Brightness.PNG" << endl << endl;

	cout << "Sobel Y is Filter loading..." << endl;
	SobelYFilter* sobelY = new SobelYFilter();
	QImage sobelYImage = sobelY->calculateNewImagePixMap(photo, 1);
	sobelYImage.save("Resources/SobelY.PNG");
	cout << "Photo is saving as Resources/SobelY.PNG" << endl << endl;

	cout << "Sobel X is Filter loading..." << endl;
	SobelXFilter* sobelX = new SobelXFilter();
	QImage sobelXImage = sobelX->calculateNewImagePixMap(photo, 1);
	sobelXImage.save("Resources/SobelX.PNG");
	cout << "Photo is saving as Resources/SobelX.PNG" << endl << endl;

	cout << "Gray World Filter is loading..." << endl;
	GrayWorldFilter* grayWorld = new GrayWorldFilter();
	QImage grayWorldImage = grayWorld->calculateNewImagePixMap(photo, 0);
	grayWorldImage.save("Resources/GrayWorld.PNG");
	cout << "Photo is saving as Resources/GrayWorld.PNG" << endl << endl;

	cout << "Histogram Linear Stretch Filter is loading..." << endl;
	HistogramLinearStretchFilter* histogramLinearScretch = new HistogramLinearStretchFilter();
	QImage histogramLinearScretchImage = histogramLinearScretch->calculateNewImagePixMap(photo, 0);
	histogramLinearScretchImage.save("Resources/HistogramLinearStretchFilter.PNG");
	cout << "Photo is saving as Resources/HistogramLinearStretchFilter.PNG" << endl << endl;*/

	cout << "########## TESTING MORPHOLOGY PROGRAM ##########" << endl << endl;

	cout << "Structure element:" << endl;
	cout << "Enter width: ";
	int width = 0;
	cin >> width;
	
	cout << "Enter height: ";
	int height = 0;
	cin >> height;
	
	cout << "Enter elements of mask (0, 1): ";
	bool* elem = new bool[width * height];
	for (int i = 0; i < width * height; i++)
		cin >> elem[i];

	Mask mask(elem, width, height);

	cout << "Your mask: " << endl;
	for (int i = 0; i < mask.GetHeight(); i++)
	{
		for (int j = 0; j < mask.GetWidth(); j++)
			cout << mask.GetMask()[i * mask.GetWidth() + j] << "\t";
		cout << endl;
	}

	cout << "Dilation Morphology is loading..." << endl;
	DilationMorphology* dilation = new DilationMorphology();
	QImage dilationImage = dilation->calculateNewImagePixMap(photo, mask);
	dilationImage.save("Resources/Dilation.PNG");
	cout << "Photo is saving as Resources/Dilation.PNG" << endl << endl;

	cout << "Erosion Morphology is loading..." << endl;
	ErosionMorphology* erosion = new ErosionMorphology();
	QImage erosionImage = erosion->calculateNewImagePixMap(photo, mask);
	erosionImage.save("Resources/Erosion.PNG");
	cout << "Photo is saving as Resources/Erosion.PNG" << endl << endl;

	cout << "Opening Morphology is loading..." << endl;
	OpeningMorphology* opening = new OpeningMorphology();
	QImage openingImage = opening->calculateNewImagePixMap(photo, mask);
	openingImage.save("Resources/Opening.PNG");
	cout << "Photo is saving as Resources/Opening.PNG" << endl << endl;

	cout << "Closing Morphology is loading..." << endl;
	ClosingMorphology* closing = new ClosingMorphology();
	QImage closingImage = closing->calculateNewImagePixMap(photo, mask);
	closingImage.save("Resources/Closing.PNG");
	cout << "Photo is saving as Resources/Closing.PNG" << endl << endl;

	cout << "Top Hat Morphology is loading..." << endl;
	TopHatMorphology* tophat = new TopHatMorphology();
	QImage tophatImage = tophat->calculateNewImagePixMap(photo, mask);
	tophatImage.save("Resources/TopHat.PNG");
	cout << "Photo is saving as Resources/TopHat.PNG" << endl << endl;
}
