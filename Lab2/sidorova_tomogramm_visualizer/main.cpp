#include "view.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View w;
	w.LoadData("..//data//testdata.bin");
	w.show();
	return a.exec();
}
