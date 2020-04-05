#include "bin.h"

#include <QMessageBox>

Bin::Bin()
{
	x = y = z = 0;
	value = nullptr;
};

Bin::~Bin()
{
	x = y = z = 0;
	delete[] value;
};
//--------------------------

void Bin::ReadBIN(QString path)
{
	char* charPath = QStringToChar(path);
	FILE* file;
	file = fopen(charPath, "rb");
	if (!file)
	{
		QMessageBox::warning(0, "Warning", "File wasn't opened!");
		return;
	}
	
	fread(&x, sizeof(int32_t), 1, file);
	fread(&y, sizeof(int32_t), 1, file);
	fread(&z, sizeof(int32_t), 1, file);
	
	value = new int16_t[x * y * z];
	for (int i = 0; i < x * y * z; i++)
		fread(value + i, sizeof(int16_t), 1, file);
	fclose(file);
};

char* Bin::QStringToChar(QString text)
{
	char* newText = new char[text.length()];
	strcpy(newText, text.toLocal8Bit().constData());
	return newText;
};