#include "tasks.h"

int tLength = 0;

void addTask(Task **tasks, int *taskCount, const char *name){
  *tasks = (Task *)realloc(*tasks, (*taskCount + 1) * sizeof(Task));
  (*tasks)[*taskCount].task = (char *)malloc(strlen(name) + 1);
  (*tasks)[*taskCount].completed = 0;
  strcpy((*tasks)[*taskCount].task, name);
  (*taskCount)++;
}

void listTasks(int index, Task *tasks) {
  printf("\n");
  for (int i = 0; i<tLength;i++){
    printf("%d.%d %s\n", index, i + 1,tasks[i].task);
  }
}

void deleteTask(int index, Task *tasks){
  if (index <= tLength && index >= 0){
    free(tasks[index].task);
    for (int i = index; i<=tLength; i++){
      tasks[i] = tasks[i + 1];
    }
    tLength--;
  } else {
    printf("Invalid Index.");
  }
}

void markTaskComplete(int index, Task* tasks) {
  tasks[index].completed = 1;
}
