#ifndef _UTILS_H_
#define _UTILS_H_

template <class T>
T Clamp(T, int, int);

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

#endif