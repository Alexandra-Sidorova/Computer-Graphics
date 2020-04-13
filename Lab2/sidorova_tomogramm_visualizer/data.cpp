#include "data.h"

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
	setlocale(0, "RUS");

	std::ifstream file;
	file.open(path.toStdString(), std::ios::binary | std::ios::in);

	if (!file.is_open())
	{
		QMessageBox::warning(0, "Warning", "File wasn't opened!");
		file.close();
		return;
	}
	
	int w, h, d;

	file.read((char*)&w, sizeof(int));
	file.read((char*)&h, sizeof(int));
	file.read((char*)&d, sizeof(int));
	
	if (w == 0 || h == 0 || d == 0)
	{
		QMessageBox::warning(0, "Warning", "File wasn't opened!");
		file.close();
		return;
	}

	file.read((char*)&scaleX, sizeof(float));
	file.read((char*)&scaleY, sizeof(float));
	file.read((char*)&scaleZ, sizeof(float));
	
	if (value != nullptr)
		delete[] value;

	x = w;
	y = h;
	z = d;

	long size = x * y * z;

	value = new short[size];
	file.read((char*)value, size * sizeof(short));
	file.close();

	MinMax();
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
};