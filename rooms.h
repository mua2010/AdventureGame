#ifndef _ROOM_HEADER
#define _ROOM_HEADER
#include "items.h"

struct Room
{
  char *name;
  char *description;
  Item *items;
  struct Room *north;
  struct Room *south;
  struct Room *east;
  struct Room *west;
  struct Room *up;
  struct Room *down;
};

typedef struct Room Room;

Room *room(char *name, char *description, Item *items,
           Room *north, Room *south,
           Room *east, Room *west,
           Room *up, Room *down);

void room_exit_north(Room *current, Room *other);

void room_exit_south(Room *current, Room *other);

void room_exit_east(Room *current, Room *other);

void room_exit_west(Room *current, Room *other);

void room_exit_up(Room *current, Room *other);

void room_exit_down(Room *current, Room *other);
#endif