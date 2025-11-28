#ifndef TASKS_H
#define TASKS_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *task;
  int completed;
} Task;

void addTask(Task **tasks, const char *name);
void listTasks(int index, Task *tasks);
void deleteTask(int index, Task *tasks);
void markTaskComplete(int index, Task* tasks);

#endif
