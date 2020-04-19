#ifndef _DIALOGMINMAX_H_
#define _DIALOGMINMAX_H_

#include <qdialog>
#include <qlineedit>

class Dialog : public QDialog
{
	Q_OBJECT
private:
	QLineEdit* max;
	QLineEdit* min;

public:
	Dialog(QWidget* parent = Q_NULLPTR);

	int Max() const
	{
		return max->text().toInt();
	}

	int Min() const
	{
		return min->text().toInt();
	}
};

#endif