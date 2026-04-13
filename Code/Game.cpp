#include "game.h"
#include <time.h>
#include <stdio.h>
extern HWND hWND;
void Game::Paint(HDC hdcMem)
{
	for(int i=BG;i<NofLayers;i++)
	{
		for(auto obj : Draw)
		{
			if(obj->Layer!=i)
				continue;
			if(obj->status==PASSIVE)
				continue;
			if(obj->type!=this->status)
				continue;
			obj->Paint(hdcMem);
		}
		for(auto obj : Creeps)
		{
			obj->Paint(hdcMem,i);
		}
		room->Paint(hdcMem,i);
		if(i==CONTROLS)
		{
			if(lastUsed!=NULL)
			{
				RECT rc;
				GetClientRect(hWND,&rc);
				this->lastUsed->Print(hdcMem,((rc.top+rc.bottom)/2)-40+(int)itemvalid,((rc.left+rc.right)/2)-50);
				if(itemvalid==0)
					lastUsed=NULL;
				itemvalid-= 0.5;
			}
		}
	}
}
Game::Game()
{
	lastUsed=NULL;
	srand(time(NULL));
	status=MENU;
	Creeps.clear();
	Draw.clear();
	Items.clear();
	itemvalid=0;
}
Game::~Game()
{
	for(auto obj:Creeps)
	{
		obj->~Living();
	}
	Creeps.clear();
	for(auto obj:Draw)
	{
		obj->~DrawableObj();
	}
	Draw.clear();
	for(auto obj:Items)
	{
		obj->~Item();
	}
	Items.clear();
}
void Game::Update()
{
	for(auto Obj:Draw)
	{
		Obj->Update();
	}
}
void Game::AddObj(DrawableObj* Obj)
{
	Draw.push_back(Obj);
}
void Game::AddObj(Living* Obj)
{
	Creeps.push_back(Obj);
}
void Game::AddObj(Item* Obj)
{
	Items.push_back(Obj);
}
void Game::AddObj(Room* Obj)
{
	Rooms.push_back(Obj);
}
Room* Game::getRoomByID(int myID)
{
	for(int i=0;i,this->Rooms.size();i++)
	{
		if(Rooms[i]->getID()==myID)
			return Rooms[i];
	}
	return this->room;
}
void Game::Init()
{
	Item* ItemA;
	Room* RoomA;
	FILE* pFile;
	int cp;
	//Load Items
	char path[144];
	fopen_s(&pFile,"Items.ldr","r");
	cp = fgetc(pFile);
	while(cp!='{') cp = fgetc(pFile);
	while(cp!='}')
	{
		while((cp!='[')&&(cp!='}')) cp = fgetc(pFile);
		if(cp=='}')
			break;
		cp = fgetc(pFile);
		for(int i=0;i<143-1;i++)
		{
			path[i]=cp;
			path[i+1]=0;
			cp = fgetc(pFile);
			if(cp==']')
				break;
		}
		ItemA = new Item();
		ItemA->Load(path);
		this->AddObj(ItemA);
		ItemA=NULL;
	}
	fclose(pFile);
	//Load Rooms
	fopen_s(&pFile,"Rooms.ldr","r");
	cp = fgetc(pFile);
	while(cp!='{') cp = fgetc(pFile);
	while(cp!='}')
	{
		while((cp!='[')&&(cp!='}')) cp = fgetc(pFile);
		if(cp=='}')
			break;
		cp = fgetc(pFile);
		for(int i=0;i<143-1;i++)
		{
			path[i]=cp;
			path[i+1]=0;
			cp = fgetc(pFile);
			if(cp==']')
				break;
		}
		RoomA = new Room();
		RoomA->Load(path);
		this->AddObj(RoomA);
		RoomA=NULL;
	}
	fclose(pFile);
	if(this->Rooms.size()>0)
		room=Rooms[0];
}
void Game::move(int Door)
{
	room = this->getRoomByID(room->move(Door));
}