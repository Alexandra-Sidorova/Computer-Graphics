#include <QImage>
#include <string>

#include "Includes/InvertFilter.h"
#include "Includes/BlurFilter.h"
#include "Includes/GaussianBlurFilter.h"

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
}
