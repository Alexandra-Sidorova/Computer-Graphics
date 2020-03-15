#include "Mask.h"

Mask::Mask()
{
	height = width = 3;
	mask = new bool[9];
	for (int i = 0; i < 9; mask[i++] = true);
};

Mask::Mask(bool* _mask, int _width, int _height) : width(_width), height(_height)
{
	mask = new bool[width * height];
	for (int i = 0; i < width * height; mask[i] = _mask[i], i++);
};

Mask::~Mask()
{
	height = width = 0;
	delete[] mask;
};
//------------------------------------

bool* Mask::GetMask() const
{
	return mask;
};

int Mask::GetWidth() const
{
	return width;
};

int Mask::GetHeight() const
{
	return height;
};

void Mask::SetMask(const bool* _mask)
{
	if (mask != nullptr)
		delete[] mask;

	mask = new bool[width * height];
	for (int i = 0; i < width * height; mask[i] = _mask[i], i++);
};

void Mask::SetWidth(const int _w)
{
	width = _w;
};

void Mask::SetHeight(const int _h)
{
	height = _h;
};