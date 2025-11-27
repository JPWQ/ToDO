#ifndef COLLECTIONS_H
#define COLLECTIONS_H
#include "tasks.h"

typedef struct {
  char *collection;
  Task *tasks;
} Collection;

void addCollection(const char *collection, Collection **collections);
void deleteCollection(int index, Collection *collections);
void addTaskToCollection(int index, const char *name, Collection *collections);
void listCollections(Collection *collections);
void freeCollections(Collection *collections);

#endif
