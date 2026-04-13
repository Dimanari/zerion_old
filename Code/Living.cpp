#include "Living.h"
#include <stdio.h>

extern HINSTANCE hinstance;
void Living::SetAvatar(DrawableObj* Obj)
{
	this->Avatar=Obj;
	printf("Living Object got An Avatar\n");
}
void Living::setXY(int x,int y)
{
	pos.X=x;
	pos.Y=y;
}
void Living::setXY(COORD pos)
{
	pos.X=pos.X;
	pos.Y=pos.Y;
}
int Living::attack()
{
	int random = (ranged+2*Luck);
	int dmg;
	if(random>0)
		dmg = AttackPower+AD+rand()%(random+1);
	else if(random<0)
		dmg = AttackPower+AD-rand()%(-random+1);
	else
		dmg = AttackPower+AD;
	if(AD>0)
		AD--;
	if(AD<0)
		AD++;
	if(Luck>0)
		Luck--;
	if(Luck<0)
		Luck++;
	printf("Living Object Deals %d damage\nData:\nAD   - %d\nLuck - %d\n",dmg,AttackPower+AD,(random)/2);
	return dmg;//the Damage
}
Living& Living::operator<<(int dmg) //Damage
{
	printf("Living Object took %d Damage\n",dmg);
	if(dmg<=0)
		return *this;
	this->HP=this->HP-dmg;
	if(this->HP<0)
		this->HP = 0;
	return *this;
}
Living& Living::operator>>(int dmg) // heal
{
	printf("Living Object was healed for %d Damage\n",dmg);
	if(dmg<=0)
		return *this;
	this->HP=this->HP+dmg;
	if(this->HP>this->maxHP)
		this->HP = maxHP;
	return *this;
}
bool Living::Alive()
{
	if(this->HP>0)
		return true;
	return false;
}
void Living::setMaxHP(int nHP)
{
	int delta=nHP-this->maxHP;
	this->maxHP = nHP;
	if(this->HP<0)
		this->HP=0;
	if(delta>0)
	{
		this->HP=+delta;
	}
	if(this->HP>this->maxHP)
	{
		this->HP=this->maxHP;
	}
}
Living::Living()
{
	this->HP=0;
	this->maxHP=0;
	this->Avatar=NULL;
	AD=0;Luck=0;
	AttackPower=0;ranged=1;
}
void Living::Paint(HDC hDC,int layer)
{
	if(layer == SRFACE)Avatar->Paint(hDC,pos.X,pos.Y);
	if(layer == CONTROLS)
	{
		char text[100];
		sprintf_s(text,"%s\n HP: %d \\ %d ",this->name,HP,maxHP);
		RECT rc;
		rc.top=pos.Y+this->Avatar->sizeY();
		rc.left=pos.X;
		rc.bottom=rc.top+20*2;//number of lines
		rc.right=rc.left+this->Avatar->sizeX();
		DrawText(hDC,text,-1,&rc, DT_CENTER);
	}
}
void Living::Load(char* path)
{
	FILE* pFile;
	fopen_s(&pFile,path,"r");
	int cp = fgetc(pFile);
	/*
	while(cp!='(') cp = fgetc(pFile);
	fscanf_s(pFile,"%d",&this->ID);
	*/
	while(cp!='[') cp = fgetc(pFile);
	cp = fgetc(pFile);
	for(int i=0;i<NAME_LENGHT-1;i++)
	{
		this->name[i]=cp;
		this->name[i+1]=0;
		cp = fgetc(pFile);
		if(cp==']')
			break;
	}
	while(cp!='(') cp = fgetc(pFile);
	int litm[5],index=0;;
	int tmpn=0;
	while(cp!=')')
	{
		if(cp == ' ')
		{
			if(tmpn==0)
			{
				cp = fgetc(pFile);
				continue;
			}
			litm[index]=tmpn;
			index++;
			tmpn=0;
		}
		if((cp>=('0'))&&(cp<=('9')))
		{
			tmpn=10*tmpn+cp-'0';
		}
		cp = fgetc(pFile);
	}
	if(tmpn!= 0 )
		litm[index]=tmpn;
	this->AttackPower=litm[0];
	this->ranged=litm[1];
	this->setMaxHP(litm[2]);
	while(cp!='[') cp = fgetc(pFile);
	char path2[144];
	cp = fgetc(pFile);
	for(int i=0;i<143;i++)
	{
		path2[i]=cp;
		path2[i+1]=0;
		cp = fgetc(pFile);
		if(cp==']')
			break;
	}
	int x,y;
	while(cp!='(') cp = fgetc(pFile);
	fscanf_s(pFile,"%d %d",&x,&y);
	fclose(pFile);
	bitmapObj* myOBG= new bitmapObj();
	myOBG->Load(hinstance,path2,x,y);
	this->SetAvatar(myOBG);
}
void Living::addAD(int val)
{
	this->AD=AD+val;
}
void Living::addLuck(int val)
{
	this->Luck=Luck+val;
}