#include "items.h"
#include <stdio.h>

Item *item(char *name_, char *description, Item *nextptr)
{
  Item *newitem = (Item *)malloc(sizeof(Item));
  if (newitem == NULL)
    return NULL;
  newitem->name = name_;
  newitem->description = description;
  newitem->next = nextptr;
  return newitem;
}

char *item_name(Item *item)
{
  if (item == NULL)
    return NULL;
  return item->name;
}

char *item_description(Item *item)
{
  if (item == NULL)
    return NULL;
  return item->description;
}

Item *item_next(Item *item)
{
  if (item->next == NULL)
    return NULL;
  else
    return item->next;
}

//given any head of list, remove the item from list and return it. return NULL otherwise
//Source Used: https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/
Item *item_take(Item **head, char *item)
{
  //store the head node
  Item *curr = *head;
  Item *prev = NULL;

  //edge case: If head node has the target item
  if (curr != NULL && (strcmp(curr->name, item) == 0))
  {
    //curr->name = &(head->name);
    *head = curr->next; // Changed head
    return curr;
  }

  // iterate over the list and stop when target item is found
  //update prev on every iteration
  while (curr != NULL && (strcmp(curr->name, item) == 0))
  {
    prev = curr;
    curr = curr->next;
  }

  // return null If item was not present in linked list
  if (curr == NULL)
    return NULL;
  // Unlink the node from linked list
  prev->next = curr->next;
  return curr;
  //free(curr);  // Free memory
  return NULL;
}

//given a head of list, prints the items in the list
void print_items(Item *item)
{
  while (item != NULL)
  {
    printf("Name: %s , Description of Item: %s\n", item->name, item->description);
    item = item->next;
  }
}

//frees a linked list of items
//item: the list of items
//method used from lecture 5 challange
Item *free_items(Item *item)
{
  if (item == NULL)
  {
    return NULL;
  }
  free_items(item->next); //free the rest of the list
  free(item);             //free this node
  return NULL;
}
