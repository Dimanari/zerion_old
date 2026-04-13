#include "Item.h"
#include <stdio.h>

void Item::use(Living* user)
{
	switch(this->type)
	{
	case Heal:
		*user>>(value);
		break;
	case AD:
		user->addAD(value);
		break;
	case Luck:
		user->addLuck(value);
		break;
	default:
		break;
	}
}
void Item::Load(char* path)
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
	switch(litm[0])
	{
	case 1:
		this->type=Heal;
	case 2:
		this->type=AD;
	case 3:
		this->type=Luck;
	default:
		this->type=Heal;
	}
	this->value=litm[1];
	fclose(pFile);
}
void Item::Print(HDC hDC,int x,int y)
{
	//print a massege of use to the screen
	RECT rc;
	rc.top=x;
	rc.left=y;
	rc.bottom=rc.top+40;
	rc.right=rc.left+100;
	char msg[144];
	sprintf_s(msg,"%s\nadd %d",this->name,this->value);
	DrawText(hDC,msg,-1,&rc,DT_CENTER);
}