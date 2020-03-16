#ifndef _UTILS_H_
#define _UTILS_H_

#include "Intensity.h"

template <class T>
T Clamp(T, int, int);

template<class T>
void SortIntensity(Intensity*, int);

template<class T>
void Swap(T&, T&);

//---------------------------------

template <class T>
T Clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;

	return v;
};

template<class T>
void SortIntensity(Intensity* _array, int _size)
{
	unsigned long i, j;

	for (i = 0; i < _size; i++)
		for (j = _size - 1; j > i; j--)
			if (_array[j - 1].value > _array[j].value)
				Swap(_array[j - 1], _array[j]);
};

template<class T>
void Swap(T& _a, T& _b)
{
	T tmp = _a;
	_a = _b;
	_b = tmp;
};

#endif