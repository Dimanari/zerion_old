#include "fullWindow.h"
extern HWND hWND;

void BackGround::Paint(HDC hDC)
{
	HDC hdcMem;
	RECT rc;
	GetClientRect(hWND,&rc);
	//create a device context for the bitmap
	hdcMem = CreateCompatibleDC(hDC);
	SelectObject(hdcMem, hBmp);

	//draw the bitmap to the window (bit block transfer)
	TransparentBlt( 
		hDC, //destination device context
		rc.left, rc.top, //x,y location on destination
		rc.right,rc.bottom , //width,height of source bitmap
		hdcMem, //source bitmap device context
		0, 0,this->size.X, this->size.Y, //start x,y on source bitmap
		RGB(0,0,0)); //Transparent Color
	//delete the device context
	DeleteDC(hdcMem);
}

void BackGround::Paint(HDC hDC,int x,int y)
{
	HDC hdcMem;
	RECT rc;
	GetClientRect(hWND,&rc);
	//create a device context for the bitmap
	hdcMem = CreateCompatibleDC(hDC);
	SelectObject(hdcMem, hBmp);

	//draw the bitmap to the window (bit block transfer)
	TransparentBlt( 
		hDC, //destination device context
		x, y, //x,y location on destination
		rc.right,rc.bottom , //width,height of source bitmap
		hdcMem, //source bitmap device context
		0, 0,this->size.X, this->size.Y, //start x,y on source bitmap
		RGB(0,0,0)); //Transparent Color
	//delete the device context
	DeleteDC(hdcMem);
}