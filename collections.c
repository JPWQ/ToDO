#include "collections.h"

int cLength = 0;

void addCollection(const char *collection, Collection **collections){
    *collections = realloc(*collections, (cLength + 1) * sizeof(Collection));

    (*collections)[cLength].collection = malloc(strlen(collection) + 1);
    strcpy((*collections)[cLength].collection, collection);
    (*collections)[cLength].tasks = NULL;
    (*collections)[cLength].taskCount = 0;
    (*collections)[cLength].index = cLength;
    cLength++;
}

void deleteCollection(int index, Collection *collections){
  if (index <= cLength && index >= 0){

    free(collections[index].collection);
    free(collections[index].tasks);

    for(int i = index; i<=cLength; i++){
      collections[i] = collections[i+1];
    }
    cLength--;
  } else {
    printf("Invalid Index.");
  }
}

void addTaskToCollection(int index, const char *name, Collection *collections){
  addTask(&collections[index].tasks,
          &collections[index].taskCount,
          name);
}

void listCollections(Collection * const collections){
  for (int i = 0; i < cLength; i++){
    printf("%d. %s\n", i + 1, collections[i].collection);
  }
}

void editCollection(int index, const char *collection, Collection **collections) {
  (*collections)[index].collection = (char *)malloc(strlen(collection) + 1);
  strcpy((*collections)[index].collection, collection);
}

void freeCollections(Collection *collections){
  for (int i=0; i<cLength; i++){
    free(collections[i].collection);
    free(collections[i].tasks);
  }
}
