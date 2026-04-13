#include "fullWindow.h"

#define NAME_LENGHT 30

enum Layers{BG,SRFACE,CONTROLS,NofLayers};
class Living
{
	DrawableObj* Avatar;
	int HP,maxHP,AttackPower,ranged,AD,Luck;
	char name[NAME_LENGHT];
public:
	COORD pos;
	void SetAvatar(DrawableObj*);
	void setXY(int,int);
	void setXY(COORD);
	void addAD(int);
	void addLuck(int);
	void setMaxHP(int);
	Living();
	virtual int attack();
	virtual void Load(char*);
	virtual Living& operator<<(int);
	virtual Living& operator>>(int);
	bool Alive();
	virtual void Paint(HDC,int);
	//not shure if ~Living(); is needed.
};