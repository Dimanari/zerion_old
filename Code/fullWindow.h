#include "bitmap.h"

class BackGround : public bitmapObj
{
public:
	virtual void Paint(HDC);
	virtual void Paint(HDC,int,int);
};