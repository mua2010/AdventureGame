#include "rooms.h"

Room *room(char *name, char *description, Item *items,
           Room *north, Room *south,
           Room *east, Room *west,
           Room *up, Room *down)
{
  Room *newRoom = (Room *)malloc(sizeof(Room));
  if (newRoom == NULL)
    return NULL;
  newRoom->name = name;
  newRoom->description = description;
  newRoom->items = items;
  newRoom->north = north;
  newRoom->south = south;
  newRoom->east = east;
  newRoom->west = west;
  newRoom->up = up;
  newRoom->down = down;
  return newRoom;
}

//set the "other" room to the north of "current" room
void room_exit_north(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->north = other;
}

void room_exit_south(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->south = other;
}

void room_exit_east(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->east = other;
}

void room_exit_west(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->west = other;
}

void room_exit_up(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->up = other;
}

void room_exit_down(Room *current, Room *other)
{
  if (current == NULL)
    return;
  current->down = other;
}