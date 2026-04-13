#include <Windows.h>

class DrawableObj
{
public:
	int status;//if it's shown or not
	int type;//where is it needed to be shown
	int Layer;//the Layer which the object will be Drawn in.
	COORD pos;//the position of the object in the screen
	virtual void Paint(HDC);//Draws the Object
	virtual void Paint(HDC,int,int);
	DrawableObj();//construct the Generic object
	DrawableObj(int,int);//construct the Generic object with base positioning
	void setLayer(int);//Change the Layer of the Object
	virtual ~DrawableObj();//Destroy the Object
	virtual void Update();
	
	virtual int sizeX();
	virtual int sizeY();
};
class Room;
class bitmapObj;
class Living;