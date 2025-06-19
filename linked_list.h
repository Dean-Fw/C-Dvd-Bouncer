#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>

struct Node {
  uint data;
  struct Node *next;
};

struct Node *createNode(uint newData);

struct Node *append(struct Node *head, uint newData);

void freeList(struct Node *head);

#endif // LINKED_LIST_H_
