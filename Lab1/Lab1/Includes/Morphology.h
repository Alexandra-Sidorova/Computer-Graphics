#ifndef _MORPHOLOGY_H_
#define _MORPHOLOGY_H_

class Morphology
{
protected:
	bool* mask;
	int weight;
	int height;

public:
	Morphology();
	Morphology(bool* _mask, int _height, int _weight);
	~Morphology() {};
};

#endif