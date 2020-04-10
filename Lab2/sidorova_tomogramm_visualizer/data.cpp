#include "data.h"

#include <qdebug.h>
#include <QMessageBox>

Data::Data() : x(0), y(0), z(0), 
	scaleX(0), scaleY(0), scaleZ(0), min(0), max(0)
{
	value = nullptr;
};

Data::~Data()
{
	x = y = z = scaleX = scaleY = scaleZ = min = max = 0;
	delete[] value;
};
//-----------------------------------------

void Data::ReadBIN(QString path)
{
	char* charPath = QStringToChar(path);
	FILE* file;
	file = fopen(charPath, "rb");
	if (!file)
	{
		QMessageBox::warning(0, "Warning", "File wasn't opened!");
		return;
	}
	
	fread(&x, sizeof(int), 1, file);
	fread(&y, sizeof(int), 1, file);
	fread(&z, sizeof(int), 1, file);
	
	fread(&scaleX, sizeof(float), 1, file);
	fread(&scaleY, sizeof(float), 1, file);
	fread(&scaleZ, sizeof(float), 1, file);
	
	value = new short[x * y * z];
	for (int i = 0; i < x * y * z; i++)
		fread(value + i, sizeof(short), 1, file);
	fclose(file);
};

short Data::GetData(int _x, int _y, int _z) const
{
	return value[_x + x * _y + x * y * _z];
};

int Data::GetWidth() const
{
	return x;
};

int Data::GetHeight() const
{
	return y;
};

int Data::GetDepth() const
{
	return z;
};

short Data::GetMax() const
{
	return max;
};

short Data::GetMin() const
{
	return min;
};

void Data::MinMax()
{
	min = max = value[0];
	for (int i = 0; i < x * y * z; i++)
	{
		if (min > value[i])
			min = value[i];
		if (max < value[i])
			max = value[i];
	}

	qDebug() << "Min = " << min << " Max = " << max;
};

short& Data::operator[](const int _idx) const
{
	return value[_idx];
};

char* Data::QStringToChar(QString text)
{
	char* newText = new char[text.length()];
	strcpy(newText, text.toLocal8Bit().constData());
	return newText;
};