#pragma once

#include <QtWidgets/QWidget>
#include "ui_tomogrammvisualizer.h"

class TomogrammVisualizer : public QWidget
{
	Q_OBJECT

public:
	TomogrammVisualizer(QWidget *parent = Q_NULLPTR);

private:
	Ui::TomogrammVisualizerClass ui;

public slots:
	void OpenDialogMenu();
	//void SetupView();

};
