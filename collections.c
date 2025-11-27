#include "collections.h"

int cLength = 0;

void addCollection(const char *collection, Collection **collections){
    *collections = realloc(*collections, (cLength + 1) * sizeof(Collection));

    (*collections)[cLength].collection = malloc(strlen(collection) + 1);
    strcpy((*collections)[cLength].collection, collection);
    (*collections)[cLength].tasks = NULL;

    cLength++;
}

void deleteCollection(int index, Collection *collections){
  if (index <= cLength && index >= 0){
    printf("%d", cLength);

    free(collections[index-1].collection);
    free(collections[index-1].tasks);

    for(int i = index-1; i<=cLength; i++){
      collections[i] = collections[i+1];
    }
    cLength--;
  } else {
    printf("Invalid Index.");
  }
}

void addTaskToCollection(int index, const char *name, Collection *collections){
  addTask(&collections[index - 1].tasks, name);
}

void listCollections(Collection * const collections){
  for (int i = 0; i < cLength; i++){
    printf("%d. %s\n", i + 1, collections[i].collection);
  }
}

void freeCollections(Collection *collections){
  for (int i=0; i<cLength; i++){
    free(collections[i].collection);
    free(collections[i].tasks);
  }
}
