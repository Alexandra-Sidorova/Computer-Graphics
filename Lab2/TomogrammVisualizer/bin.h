#ifndef _BIN_H_
#define _BIN_H_

#include <string>
#include <cstdio>
#include <cstdint>
#include <qstring.h>

using namespace std;

class Bin
{
public:
	int32_t x, y, z;
	int16_t* value;

	Bin();
	~Bin();

	void ReadBIN(QString path);

private:
	char* QStringToChar(QString text);
};


#endif