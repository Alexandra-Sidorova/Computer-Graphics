#ifndef _DATA_H_
#define _DATA_H_

#include <string>
#include <cstdio>
#include <fstream>
#include <locale>
#include <qstring.h>

class Data
{
private:
	float scaleX, scaleY, scaleZ;
	int x, y, z;
	short* value;
	short min, max;

public:
	Data();
	~Data();

	void ReadBIN(QString path);

	short GetData(int _x, int _y, int _z) const;
	int GetWidth() const;
	int GetHeight() const;
	int GetDepth() const;
	short GetMax() const;
	short GetMin() const;

	void MinMax();
};

#endif