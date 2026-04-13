#include "game.h"

void DrawableObj::Paint(HDC hdcMem)
{
	Rectangle(hdcMem, pos.X, pos.Y, pos.X+50, pos.Y+50);
	return;
}
void DrawableObj::Paint(HDC hdcMem,int x,int y)
{
	Rectangle(hdcMem, x, y, x+50, y+50);
	return;
}
DrawableObj::DrawableObj():status(TODRAW),type(MENU)
{
	pos.X=20;
	pos.Y=50;
	Layer=BG;
}
DrawableObj::DrawableObj(int status,int type):status(status),type(type)
{
	pos.X=20;
	pos.Y=50;
	Layer=BG;
}
DrawableObj::~DrawableObj()
{
}
void DrawableObj::setLayer(int tL)
{
	Layer = tL;
}
void DrawableObj::Update()
{
	this->pos.X+=1+rand()%3;
	if(this->pos.X>500)
		this->pos.X=10;
}
int DrawableObj::sizeX()
{
	return 50;
}
int DrawableObj::sizeY()
{
	return 50;
}
