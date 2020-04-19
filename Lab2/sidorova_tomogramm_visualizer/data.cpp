#include "data.h"

#include <QMessageBox>

Data::Data() : width(0), height(0), depth(0), 
	scaleX(0), scaleY(0), scaleZ(0), min(0), max(0)
{
	value = nullptr;
};

Data::~Data()
{
	width = height = depth = 0;
	scaleX = scaleY = scaleZ = 0;
	min = max = 0;
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
		//QMessageBox::warning(0, "Warning", "File wasn't opened!");
		file.close();
		return;
	}
	
	int w, h, d;

	file.read((char*)&w, sizeof(int));
	file.read((char*)&h, sizeof(int));
	file.read((char*)&d, sizeof(int));
	
	if (w == 0 || h == 0 || d == 0)
	{
		//QMessageBox::warning(0, "Warning", "Incorrect data!");
		file.close();
		return;
	}

	file.read((char*)&scaleX, sizeof(float));
	file.read((char*)&scaleY, sizeof(float));
	file.read((char*)&scaleZ, sizeof(float));
	
	if (value != nullptr)
		delete[] value;

	width = w;
	height = h;
	depth = d;

	long size = width * height * depth;

	value = new short[size];
	file.read((char*)value, size * sizeof(short));
	file.close();

	MinMax();
};

int Data::GetWidth() const
{
	return width;
};

int Data::GetHeight() const
{
	return height;
};

int Data::GetDepth() const
{
	return depth;
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
	for (int i = 0; i < width * height * depth; i++)
	{
		if (min > value[i])
			min = value[i];
		if (max < value[i])
			max = value[i];
	}
};

short& Data::operator[](const int idx)
{
	return value[idx];
};