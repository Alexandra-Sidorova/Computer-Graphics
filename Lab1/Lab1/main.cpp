#include <QImage>
#include <string>

#include "Includes/InvertFilter.h"
#include "Includes/BlurFilter.h"
#include "Includes/GaussianBlurFilter.h"
#include "Includes/WavesFilter.h"
#include "Includes/MirrorFilter.h"
#include "Includes/SharpnessFilter.h"
#include "Includes/MotionBlurFilter.h"

using namespace std;

void main(int argc, char *argv[])
{
	string s;
	QImage photo;

	for (int i = 0; i < argc; i++)
		if (!strcmp(argv[i], "-p") && (i + 1 < argc))
			s = argv[i + 1];

	photo.load(QString(s.c_str()));
	photo.save("Starting.PNG");

	InvertFilter* invert = new InvertFilter();
	QImage invertImage = invert->calculateNewImagePixMap(photo, 0);
	invertImage.save("Invert.PNG");

	BlurFilter* blur = new BlurFilter();
	QImage blurImage = blur->calculateNewImagePixMap(photo, 1);
	blurImage.save("Blur.PNG");

	GaussianBlurFilter* gaussianBlur = new GaussianBlurFilter();
	QImage gaussianBlurImage = gaussianBlur->calculateNewImagePixMap(photo, 3);
	gaussianBlurImage.save("GaussianBlur.PNG");

	WavesFilter* wavesHorizontal = new WavesFilter();
	QImage wavesHorizontalImage = wavesHorizontal->calculateNewImagePixMap(photo, 0);
	wavesHorizontalImage.save("WavesHorizontal.PNG");

	WavesFilter* wavesVertical = new WavesFilter(0);
	QImage wavesVerticalImage = wavesVertical->calculateNewImagePixMap(photo, 0);
	wavesVerticalImage.save("WavesVertical.PNG");

	MirrorFilter* mirror = new MirrorFilter();
	QImage mirrorImage = mirror->calculateNewImagePixMap(photo, 0);
	mirrorImage.save("Mirror.PNG");

	SharpnessFilter* sharpness = new SharpnessFilter();
	QImage sharpnessImage = sharpness->calculateNewImagePixMap(photo, 1);
	sharpnessImage.save("Sharpness.PNG");

	MotionBlurFilter* motionBlur = new MotionBlurFilter();
	QImage MotionBlurImage = motionBlur->calculateNewImagePixMap(photo, 1);
	MotionBlurImage.save("MotionBlur.PNG");
}
