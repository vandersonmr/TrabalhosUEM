#ifndef LIST_H
#define LIST_H

typedef struct Node Node;
typedef struct Fun Fun;

struct Fun {
  char* body;
  Node* arguments;
};

struct Node {
  char  *name;
  float value;
  Node  *next;
  Fun   *func;
};

void insert(Node*, Node*);
Node *get(Node*, char*);
void init(Node**);

#endif

