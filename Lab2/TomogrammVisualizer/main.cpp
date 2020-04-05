#include "tomogrammvisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TomogrammVisualizer w;
	w.show();
	return a.exec();
}
