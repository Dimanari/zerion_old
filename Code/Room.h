#include "Item.h"
#include <vector>
#define TEXT_LENGHT 256


class Room
{
	char name[NAME_LENGHT];
	DrawableObj* BGO;
	char text[TEXT_LENGHT];
	bool visited;
	int ID;
	std::vector<int> Doors;
	std::vector<Living*> Creeps;
public:
	int getID();
	Room();
	virtual void Load(char*);
	virtual void SetBG(DrawableObj*);
	virtual void Paint(HDC,int);
	virtual int move(char);
};