#include "Room.h"
#include <stdio.h>
/*
#pragma once
#pragma comment(lib ,"Msimg32.lib")
//**/
extern HWND hWND;
extern HFONT hfnt;
extern HFONT bigfont;
extern HINSTANCE hinstance;
Room::Room()
{
	visited=false;
	BGO=NULL;
	Creeps.clear();
}
void Room::Load(char* path)
{
	FILE* pFile;
	fopen_s(&pFile,path,"r");
	int cp = fgetc(pFile);
	while(cp!='(') cp = fgetc(pFile);
	fscanf_s(pFile,"%d",&this->ID);

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
	printf("Room Name:%s\n",this->name);
	while(cp!='[') cp = fgetc(pFile);
	cp = fgetc(pFile);
	for(int i=0;i<TEXT_LENGHT-1;i++)
	{
		this->text[i]=cp;
		this->text[i+1]=0;
		if(cp==10)
		{
			i++;
			this->text[i]=13;
			this->text[i+1]=0;
		}
		cp = fgetc(pFile);
		if(cp==']')
			break;
	}
	char path[144];
	while(cp!='[') cp = fgetc(pFile);
	cp = fgetc(pFile);
	for(int i=0;i<TEXT_LENGHT-1;i++)
	{
		path[i]=cp;
		path[i+1]=0;
		if(cp==10)
		{
			i++;
			path[i]=13;
			path[i+1]=0;
		}
		cp = fgetc(pFile);
		if(cp==']')
			break;
	}
	int x,y;
	while(cp!='(') cp = fgetc(pFile);
	fscanf_s(pFile,"%d %d",&x,&y);

	BackGround* myOBG= new BackGround();
	myOBG->Load(hinstance,path,x,y);
	this->SetBG(myOBG);

	while(cp!='[') cp = fgetc(pFile);
	int tmpn=0;
	while(cp!=']')
	{
		if(cp == ' ')
		{
			if(tmpn==0)
			{
				cp = fgetc(pFile);
				continue;
			}
			this->Doors.push_back(tmpn);
			tmpn=0;
		}
		if((cp>=('0'))&&(cp<=('9')))
		{
			tmpn=10*tmpn+cp-'0';
		}
		cp = fgetc(pFile);
	}
	if(tmpn!= 0 )
		this->Doors.push_back(tmpn);

	cp = fgetc(pFile);
	while(cp!='{') cp = fgetc(pFile);
	char pathA[144];
	pathA[0]=0;
	Living* CreepA;
	while(cp!='}')
	{
		while((cp!='[')&&(cp!='}')) cp = fgetc(pFile);
		if(cp=='}')
			break;
		cp = fgetc(pFile);
		for(int i=0;i<143-1;i++)
		{
			pathA[i]=cp;
			pathA[i+1]=0;
			cp = fgetc(pFile);
			if(cp==']')
				break;
		}
		CreepA = new Living();
		CreepA->Load(pathA);
		CreepA->setXY(rand()%600,rand()%400);
		Creeps.push_back(CreepA);
		CreepA=NULL;
	}
	fclose(pFile);
	
}
void Room::SetBG(DrawableObj* Obj)
{
	this->BGO=Obj;
	printf("Room got A Back-Ground\n");
}
void Room::Paint(HDC hDC,int layer)
{
	for(int i=0;i<Creeps.size();i++)
		Creeps[i]->Paint(hDC,layer);
	if(layer==BG)
	{
		if(BGO==NULL)
			return;
		this->BGO->Paint(hDC,0,0);
	}
	if(layer==CONTROLS)
	{
		RECT rc;
		GetClientRect(hWND,&rc);
		SelectObject(hDC, bigfont);
		DrawText(hDC,name,-1,&rc, DT_CENTER);
		rc.top = rc.bottom-(rc.bottom/5);
		SelectObject(hDC, hfnt);
		DrawText(hDC,text,-1,&rc, DT_CENTER);
	}
}
int Room::move(char num)
{
	if(num<this->Doors.size())
	{
		printf("%d ",this->Doors[num]);
		return this->Doors[num];
	}
	printf("%d ",this->Doors[num]);
	return this->ID;
}
int Room::getID()
{
	return this->ID;
}