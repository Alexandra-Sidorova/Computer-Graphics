#include <QImage.h>
#include <QString.h>
#include <QTextStream>
#include <iostream>

using namespace std;

void main()
{
	QString path;
	QTextStream cin(stdin);
	QImage image, imageReverse, imageMatrix;

	cout << "Enter the path to image: ";
	cin >> path;

	image.load(path);
	cout << "Image is loaded..." << endl;
	imageReverse = image;
	imageMatrix = image;

	// Reverse
	for(int i = 0; i < image.width(); i++)
		for (int j = 0; j < image.height(); j++)
		{
			QColor color = image.pixel(i, j);
			color.setRed(255 - color.red());
			color.setGreen(255 - color.green());
			color.setBlue(255 - color.blue());
			imageReverse.setPixelColor(i, j, color);
		}

	imageReverse.save("Reverse.png", "PNG");
	cout << "Reverse image is saved as 'Reverse.png'...";

	//// Matrix
	//for (int i = 0; i < image.width(); i++)
	//	for (int j = 0; j < image.height(); j++)
	//	{
	//		QColor color = image.pixel(i, j);
	//		for (int x = i - 1; x < i + 2; x++)
	//			for (int y = j - 1; y < j + 2; y++)
	//				color += image.pixel(x, y);
	//		
	//		imageReverse.setPixelColor(i, j, color);
	//	}
}
