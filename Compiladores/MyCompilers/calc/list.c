#include <string.h>
#include "list.h"

void init(Node** head) {
  free(*head);
  (*head)        = malloc(sizeof(Node));
  (*head)->name  = malloc(sizeof(char)*5);
  (*head)->value = 0;
  strcpy((*head)->name, "zero");
}

void insert(Node* head, Node* no) {
  Node *next = head;
  if(head == NULL) {
    return;
  }
  while(next->next != NULL) next = next->next;  
  next->next = no;
}

Node *get(Node* head, char* name) {
  Node *next = head;
  if(head == NULL) return NULL;
  while(next != NULL) {
    if(strcmp(name, next->name) == 0) return next;
    next = next->next;
  }
  return NULL;
}
