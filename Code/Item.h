#include "Living.h"

class Item
{
	enum Itype{Heal,AD,Luck};
	Itype type;
	int value;
	char name[NAME_LENGHT];
public:
	virtual void use(Living*);
	virtual void Load(char*);
	virtual void Print(HDC,int,int);
};