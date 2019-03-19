#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <stdbool.h>

#define backpack_limit 2

bool isDemon_Dead = false; // game terminates when true
bool isAlive = true;       // life of Avatar
bool basement_Lock = true; // variable used as a lock for the basement door
bool quit = false;

struct Avatar
{
  char *description; //description of the demonologist
  Item *backpack;    //list of items in the backpack
  int backpack_size; //current size of the packpack
  Room *room;        // avatar's current position in the house
};

typedef struct Avatar Avatar;

//This function stores an item in the backpack. Also removes that item from the room it was picked from.
//void pickItem(Avatar *avatar, Item *item_)
void pickItem(Avatar *avatar, char *item_)
{
  if (avatar->backpack_size >= backpack_limit)
  {
    printf("Your Backpack is Full!\n");
    return;
  }
  //remove the item from room and store it into a variable called "storeItem"
  Item *storeItem = item_take(&(avatar->room->items), item_);
  printf("%s successfully picked up\n", storeItem->name);
  if (storeItem != NULL)
  {
    //store the item into the backpack
    avatar->backpack = item(storeItem->name, storeItem->description, avatar->backpack);
    avatar->backpack_size++;
  }
  else
  {
    free(storeItem);
    storeItem = NULL;
    printf("Item not found in this area!\n");
  }
}

//function to drop an item from the backpack
void dropItem(Avatar *avatar, char *item_)
{
  if (avatar->backpack_size > 0)
  {
    //remove the item from backpack and store it in the variable "drop_Item"
    Item *drop_Item = item_take(&(avatar->backpack), item_);
    if (drop_Item != NULL)
    {
      //store the item into the current area
      avatar->room->items = item(drop_Item->name, drop_Item->description, avatar->room->items);
      avatar->backpack_size--;
    }
    else
    {
      free(drop_Item);
      drop_Item = NULL;
      printf("Item not found in the Backpack!\n");
    }
  }
  else
    printf("Your Backpack is empty\n");
}

//prints the description of the current room
void look(Room *currRoom)
{
  printf("%s", currRoom->description);
  if (currRoom->items != NULL)
  {
    printf("You can see the following items in the room:\n");
    print_items(currRoom->items);
  }
}

//return true if the item was found in the backpack, false otherwise
bool is_in_backpack(Avatar *avatar, char *item)
{
  if (avatar->backpack_size > 0)
  {
    //findItem: variable to store item in the avatar's backpack
    Item *findItem;
    if (avatar->backpack != NULL)
    {
      findItem = avatar->backpack;
    }
    else
    {
      return false;
    }
    //iterate over the items to find the target item
    while (findItem != NULL)
    {
      if (strcmp(findItem->name, item) == 0)
      {
        return true; //item found
      }
      findItem = findItem->next;
    }
    return false; //item not found
  }
  else
    return false; //backpack empty
}

//move around in the house
void move(Avatar *avatar, char *direction)
{
  if (strcmp(direction, "north") == 0 && avatar->room->north != NULL)
  {
    if (strcmp(avatar->room->name, "2nd_Floor") == 0) //trying to go to Dalton's room
    {
      if (is_in_backpack(avatar, "holy-water"))
      {
        printf("You see the demon infront of you. what to do next?\n"); //have an option to kill demon
        avatar->room = avatar->room->north;
        return;
      }
      else
      {
        isAlive = false; //you lose because no holy water
      }
    }
    avatar->room = avatar->room->north;
    look(avatar->room);
    return;
  }
  else if (strcmp(direction, "south") == 0 && avatar->room->south != NULL)
  {
    avatar->room = avatar->room->south;
    look(avatar->room);
    return;
  }
  else if (strcmp(direction, "east") == 0 && avatar->room->east != NULL)
  {
    avatar->room = avatar->room->east;
    look(avatar->room);
    return;
  }
  else if (strcmp(direction, "west") == 0 && avatar->room->west != NULL)
  {
    avatar->room = avatar->room->west;
    look(avatar->room);
    return;
  }
  else if (strcmp(direction, "up") == 0 && avatar->room->up != NULL)
  {
    avatar->room = avatar->room->up;
    look(avatar->room);
    return;
  }
  else if (strcmp(direction, "down") == 0 && avatar->room->down != NULL)
  {
    if (strcmp(avatar->room->name, "Main_Floor") == 0 && basement_Lock)
    {

      if (is_in_backpack(avatar, "key"))
      {
        printf("you need to open the door\n"); // use key
        return;
      }

      else
      {
        printf("You need a key to go to the basement\n"); //find key
        return;
      }
    }
    else if (strcmp(avatar->room->name, "2nd_Floor") == 0)
    {
      avatar->room = avatar->room->down;
      look(avatar->room);
      return;
    }
    else if (strcmp(avatar->room->name, "Main_Floor") == 0 && !basement_Lock)
    {
      avatar->room = avatar->room->down;
      look(avatar->room);
    }
  }
  else
  {
    printf("You can't go there find something else\n");
  }
}

//use an item to change the state of game/room
void useItem(Avatar *avatar, char *item)
{
  if (strcmp(item, "key") == 0) //if the item is key
  {
    if (is_in_backpack(avatar, "key") == true) //and it is in backpack
    {
      basement_Lock = false; //unlock basement
      return;
    }
    else
    {
      printf("This item is not in your backpack! \n");
      return;
    }
  }
  else if (strcmp(item, "emf-meter") == 0)
  {
    if (is_in_backpack(avatar, "emf-meter"))
    {
      if (strcmp(avatar->room->name, "2nd_Floor") == 0 || strcmp(avatar->room->name, "Bathroom1") == 0 || strcmp(avatar->room->name, "Storage_Room") == 0)
      {
        printf("emf meter points towards Dalton's room\n \n");
      }
      else
      {
        printf("emf meter points upwards \n \n");
      }
    }

    if (!is_in_backpack(avatar, "emf-meter"))
    {

      printf("This item is not in your backpack! \n");
      return;
    }
  }
  else if (strcmp(item, "holy-water") == 0)
  {
    if (is_in_backpack(avatar, "holy-water"))
    {
      if (strcmp(avatar->room->name, "Dalton's_Room") == 0)
      {
        isDemon_Dead = true; //use holy water to kill deamon
        return;
      }
    }
    {
      printf("This item is not in your backpack! \n");
      return;
    }
  }
}

//used the follwoing site to understand the scanning of input with whitespaces
//https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

//this function reads the input from the user and returns the corrosponding integer values for the task
/*
0 = look
1 = inventory
2 = go
3 = take
4 = use
5 = drop
6 = quit
-1 = any other invalid command
*/
int readInput(char *input1, char *input2)
{
  //return_input: variable to store the corrosponding integer values for the task.
  int return_input = -1;
  printf("What's next?\n");
  scanf(" %s", input1);
  if (strcmp(input1, "look") == 0)
  {
    return_input = 0;
  }
  else if (strcmp(input1, "inventory") == 0)
  {
    return_input = 1;
  }
  else if (strcmp(input1, "quit") == 0)
  {
    return_input = 6;
  }
  //if one word (look or inventory) is entered then return the corresponding integer.
  if (return_input == 0 || return_input == 1 || return_input == 6)
  {
    return return_input;
  }
  //else if the input is two different words (eg use item, go east etc) then also store the second part of command in "input2" so that it can be passed to "move" function to enable the avatar to move in the specified direction.
  scanf(" %s", input2);
  if (strcmp(input1, "go") == 0)
  {
    return_input = 2;
  }
  else if (strcmp(input1, "take") == 0)
  {
    return_input = 3;
  }
  else if (strcmp(input1, "use") == 0)
  {
    return_input = 4;
  }
  else if (strcmp(input1, "drop") == 0)
  {
    return_input = 5;
  }

  return return_input; //if invalid command, -1 is returned
}

void play(Avatar *avatar, Room *start)
{
  //input1: variable to store the first part of command
  char *input1 = (char *)malloc(sizeof(char));
  //input2: variable to store the item/direction
  char *input2 = (char *)malloc(sizeof(char));
  //command: variable to store the corrosponding integer value for the task
  int command;
  Item *curr_item;
  //****TODO: add code to quit the game when "quit" is read

  while (!isDemon_Dead && isAlive && !quit)
  {
    command = readInput(input1, input2);
    while (command == -1)
    {
      if (command == -1) //invalid command
      {
        printf("Please enter a valid command!\n");
      }
      command = readInput(input1, input2);
    }

    switch (command)
    {
    case 0: //look
      look(avatar->room); 
      break;
    case 1: //inventory
      if (avatar->backpack_size == 0)
        printf("Inventory empty\n");
      else
        print_items(avatar->backpack);
      break;
    case 2: //go
      move(avatar, input2);
      break;
    case 3: //take
      pickItem(avatar, input2);
      break;
    case 4: //use
      useItem(avatar, input2);
      break;
    case 5: //drop
      dropItem(avatar, input2);
      break;
    case 6: //quit
      quit = true;
      break;
    default:
      break;
    }
  } //end while
  free(input1);
  free(input2);
}

void make_map(Avatar *avatar)
{
  //Descriptions of the items
  char *parent_room_item_info = "This is a bronze key which can open doors\n";
  char *basement_item_info = "This will direct you towards the demon\n";
  char *storage_room_item_info = "can be used to kill demons";

  //setup items
  Item *parent_room_item = item("key", parent_room_item_info, NULL);
  Item *basement_item = item("emf-meter", basement_item_info, NULL);
  Item *storage_room_item = item("holy-water", storage_room_item_info, NULL);

  //**************************

  //Descriptions of the rooms
  char *main_info = "You are now on the main floor.\nThere is parent's room in the north.\nStairs to go down in the basement, stairs to go up to the second floor.\n";
  char *parent_room_info = "You are now inside parents room.\n";
  char *basement_info = "You are now in the basement.\nThe room is not well lit and you heard someone passing behind you.\nThere are stairs to go up to the main floor.\n";
  char *second_floor_info = "You are now on the second floor, this floor is very creepy and you can hear creepy noises.\nYou can see a room on the north and a room on the south.\nThere is also a bathroom on the west.\nThere are stairs to go down to the main floor.\n";
  char *bathroom_2_info = "There is absolute darkness in the bathroom, you can not see anything.\n";
  char *daltons_room_info = "You are now in Dalton's.\n";
  char *bathroom_1_info = "There is absolute darkness in the bathroom, you can not see anything.\n";
  char *storage_room_info = "You are now in the storage room.\n";
  
  //setup rooms
  Room *main = room("Main_Floor", main_info, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  avatar->room = main;
  Room *parent_room = room("Parent's_Room", parent_room_info, parent_room_item, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *basement = room("Basement", basement_info, basement_item, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *second_floor = room("2nd_Floor", second_floor_info, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *bathroom_2 = room("Bathroom2", bathroom_2_info, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *daltons_room = room("Dalton's_Room", daltons_room_info, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *bathroom_1 = room("Bathroom1", bathroom_1_info, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  Room *storage_room = room("Storage_Room", storage_room_info, storage_room_item, NULL, NULL, NULL, NULL, NULL, NULL);

  //*************************
  //connect the rooms

  //connections for the main floor
  room_exit_down(main, basement);
  room_exit_up(main, second_floor);
  room_exit_north(main, parent_room);
  room_exit_south(parent_room, main);

  //connections for the basement
  room_exit_up(basement, main);
  room_exit_south(basement, bathroom_2);
  room_exit_north(bathroom_2, basement);

  //connections for the second floor
  room_exit_down(second_floor, main);
  room_exit_south(second_floor, storage_room);
  room_exit_north(storage_room, second_floor);
  room_exit_west(second_floor, bathroom_1);
  room_exit_east(bathroom_1, second_floor);
  room_exit_north(second_floor, daltons_room);
  room_exit_south(daltons_room, second_floor);
}

//frees all the rooms and items in the rooms
void free_rooms(Room* room)
{
  Room *temp = room;
  room = room->north; //goto parents room
  free_items(temp->items); //free the item in parents room(key)
  free(temp); //free the parent room

//*********************
  //now goto basement
  Room *temp1 = room;
  room = room->down->south; //goto bathroom2
  free(temp1); //free bathroom2

  temp1 = room;
  room = room->down; //goto basement
  free_items(temp->items); //free the item in basement(emf meter)
  free(temp1); //free basement

  //**************
  //now free the 2nd floor rooms and items
  Room *temp2 = room;

  //now from 2nd floor,...
  room = room->up->south; //goto storage room
  free_items(temp->items); //free the item in storage room(holy water)
  free(temp2); //free storage room

  temp2 = room;
  room = room->up->west; //goto bathroom 1
  free(temp2); //free bathroom 1

  temp2 = room;
  room = room->up->north; //goto Dalton's room
  free(temp2); //free Dalton's room

  temp2 = room;
  room = room->up; //goto 2nd floor
  free(temp2); //free 2nd floor
}

int main(void)
{
  printf("***********************************\nWelcome to this Text Adventure Game\n***********************************\n");
  //printf("You are a demonologist who came to investigate\na haunted house.Find the demon and kill it\nto win the game\n\n");
  printf("Dalton is possessed by a demon.\nYou are here to kill the demon and help Dalton.\nTo play this game you have to type short phrases in the command line window.\nIf you type the word \"look\" then the game will give you a description of your surrounding.\nIf you type \"inventory\" the game will tell you the items you are carrying with you in your backpack.\nIf you type \"go DIRECTION\" where DIRECTION can be north, south, east, west, up, down. This should allow you to move the avatar through each room\nIf you type \"take ITEM\" where ITEM can be any item present in the room eg. key. This will add the item in the backpack. \nIf you type \"drop ITEM\" where ITEM can be any item present in your backpack. This will remove the item from your backpack \n \n");
  Room *home;
  Avatar avatar = {"You are a demonologist who came to investigate a haunted house and kill the deamon.\n", NULL, 0, home};
  make_map(&avatar);
  home = avatar.room;
  play(&avatar, home);
  if (isDemon_Dead)
  {
    printf("YOU WIN because you killed the demon\n");
  }

  if (!isAlive)
  {
    printf("YOU LOST because the demon killed you\n");
  }
  if (quit)
  {
    printf("Thanks for playing the game\n");
  }

  free_items(avatar.backpack);
  free_rooms(avatar.room);

  return 0;
}