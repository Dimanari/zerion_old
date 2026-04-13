#include "bitmap.h"
#include <stdio.h>
#pragma once
#pragma comment(lib ,"Msimg32.lib")
extern HINSTANCE hinstance;
void bitmapObj::Paint(HDC hDC)
{
	HDC hdcMem;

	//create a device context for the bitmap
	hdcMem = CreateCompatibleDC(hDC);
	SelectObject(hdcMem, hBmp);

	//draw the bitmap to the window (bit block transfer)
	TransparentBlt( 
		hDC, //destination device context
		this->pos.X, this->pos.Y, //x,y location on destination
		this->size.X, this->size.Y, //width,height of source bitmap
		hdcMem, //source bitmap device context
		0, 0,this->size.X, this->size.Y, //start x,y on source bitmap
		RGB(0,0,0)); //Transparent Color
	//delete the device context
	DeleteDC(hdcMem);
}
void bitmapObj::Paint(HDC hDC,int x ,int y)
{
	HDC hdcMem;

	//create a device context for the bitmap
	hdcMem = CreateCompatibleDC(hDC);
	SelectObject(hdcMem, hBmp);

	//draw the bitmap to the window (bit block transfer)
	TransparentBlt( 
		hDC, //destination device context
		x, y, //x,y location on destination
		this->size.X, this->size.Y, //width,height of source bitmap
		hdcMem, //source bitmap device context
		0, 0,this->size.X, this->size.Y, //start x,y on source bitmap
		RGB(0,0,0)); //Transparent Color
	//delete the device context
	DeleteDC(hdcMem);
}

void bitmapObj::Load(HINSTANCE hIns,LPCSTR path,int sx,int sy)
{
	this->hBmp = (HBITMAP)LoadImage( NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(hBmp==NULL)
	{
		printf("Fatal Error: Loading file %s!\nError Code:%d\n",path,GetLastError());
		return;
	}
	this->size.X=sx;
	this->size.Y=sy;
}
bitmapObj::~bitmapObj()
{
	DeleteObject( hBmp);
}
int bitmapObj::sizeX()
{
	return size.X;
}
int bitmapObj::sizeY()
{
	return size.Y;
}