#include "linked_list.h"
#include <stdlib.h>

struct Node *createNode(uint newData) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = newData;
  newNode->next = newNode;

  return newNode;
}

struct Node *append(struct Node *head, uint newData) {
  struct Node *newNode = createNode(newData);

  if (head == NULL) {
    return newNode;
  }

  struct Node *tail = head;

  while (tail->next != head) {
    tail = tail->next;
  }

  tail->next = newNode;
  newNode->next = head;

  return head;
}

void freeList(struct Node *head) {
  if (head == NULL) {
    return;
  }

  struct Node *next = head;

  while (next != NULL) {
    struct Node *prev = next;
    prev->next = NULL;

    free(prev);

    next = next->next;
  }
}
