#include "Room.h"
enum{TODRAW,PASSIVE};
enum{MENU,INGAME};

class Game //Handles anything in the game
{
	int status;
	std::vector<DrawableObj*> Draw;
	std::vector<Living*> Creeps;
	std::vector<Room*> Rooms;
	std::vector<Item*> Items;
	Room *room;
	
public:
	Item* lastUsed;
	float itemvalid;
	Room* getRoomByID(int);
	void Paint(HDC);
	Game();
	~Game();
	void Init();
	void Update();
	void AddObj(DrawableObj*);
	void AddObj(Living*);
	void AddObj(Item*);
	void AddObj(Room*);
	void move(int);
};