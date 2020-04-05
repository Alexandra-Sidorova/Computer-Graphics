#include "tomogrammvisualizer.h"
#include "bin.h"

#include <QFileDialog.h>

TomogrammVisualizer::TomogrammVisualizer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
};
//------------------------------------

void TomogrammVisualizer::OpenDialogMenu()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Open binary file"), "", tr("*.bin"));
	if (file.length() <= 1)
		return;

	Bin bin;
	bin.ReadBIN(file);
};
