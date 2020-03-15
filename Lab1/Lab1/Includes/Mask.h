#ifndef _MASK_H_
#define _MASK_H_

class Mask
{
private:
	bool* mask;
	int width;
	int height;

public:
	Mask();
	Mask(bool* _mask, int _width, int _height);
	~Mask();

	bool* GetMask() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetMask(const bool*);
	void SetWidth(const int);
	void SetHeight(const int);
};

#endif