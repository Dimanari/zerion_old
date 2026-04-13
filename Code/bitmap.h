#include "DrawableObj.h"

class bitmapObj : public DrawableObj
{
protected:
	HBITMAP hBmp;
	COORD size;
public:
	virtual void Paint(HDC);
	virtual void Paint(HDC,int,int);
	void Load(HINSTANCE,LPCSTR,int,int);
	virtual int sizeX();
	virtual int sizeY();
	virtual ~bitmapObj();
};