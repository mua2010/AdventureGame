#ifndef _ITEM_HEADER
#define _ITEM_HEADER

#include <stdlib.h>
#include <string.h>

struct Item
{
    char *name;
    char *description;
    struct Item *next;
};

typedef struct Item Item;

Item *item(char *name, char *description, Item *nextptr);

char *item_name(Item *item);

char *item_description(Item *item);

Item *item_next(Item *item);

Item *item_take(Item **head, char *item);

void print_items(Item *item);

Item *free_items(Item *item);

#endif