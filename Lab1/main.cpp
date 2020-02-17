#include <QImage.h>
#include <QString.h>
#include <QTextStream>
#include <iostream>

using namespace std;

void main()
{
	QString path;
	QTextStream cin(stdin);
	QImage image, imageReverse, imageMiddle;

	cout << "Enter the path to image: ";
	cin >> path;

	image.load(path);
	cout << "Image is loaded..." << endl;
	imageReverse = image;
	imageMiddle = image;

	// Reverse
	for(int i = 0; i < image.width(); i++)
		for (int j = 0; j < image.height(); j++)
		{
			QColor color = image.pixel(i, j);
			imageReverse.setPixelColor(i, j, QColor(255 - color.red(), 255 - color.green(), 255 - color.blue()));
		}

	imageReverse.save("reverse.png", "PNG");
	cout << "Reverse image is saved as 'reverse.png'..." << endl;

	// Middle
	for (int i = 1; i < image.width() - 1; i++)
		for (int j = 1; j < image.height() - 1; j++)
		{
			QColor color;
			for (int x = i - 1; x < i + 2; x++)
				for (int y = j - 1; y < j + 2; y++)
				{
					QColor colorPixel = image.pixel(x, y);
					color.setRed(color.red() + colorPixel.red() / 9);
					color.setGreen(color.green() + colorPixel.green() / 9);
					color.setBlue(color.blue() + colorPixel.blue() / 9);
				}
			imageMiddle.setPixelColor(i, j, color);
		}

	imageMiddle.save("middle.png", "PNG");
	cout << "Middle image is saved as 'middle.png'..." << endl;
}
