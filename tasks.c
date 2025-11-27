#include "tasks.h"

int tLength = 0;

void addTask(Task **tasks, const char *name){
  *tasks = (Task *)realloc(*tasks, (tLength + 1) * sizeof(Task));
  (*tasks)[tLength].task = (char *)malloc(strlen(name) + 1);
  (*tasks)[tLength].completed = 0;
  strcpy((*tasks)[tLength].task, name);
  tLength++;
}

void listTasks(int index, Task *tasks){
  printf("\n");
  for (int i = 0; i<tLength;i++){
    printf("%d.%d %s\n", index, i + 1,tasks[i].task);
  }
}

void deleteTask(int index, Task *tasks){
  if (index <= tLength && index > 0){
    free(tasks[index].task);
    for (int i = index; i<=tLength; i++){
      tasks[i] = tasks[i + 1];
    }
    tLength--;
  } else {
    printf("Invalid Index.");
  }
}
