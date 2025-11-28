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

void addTask(Task **tasks, int *taskCount, const char *name);
void listTasks(int index, Task *tasks);
void deleteTask(int index, int *taskCount, Task *tasks);
void editTask(int index, Task** tasks, const char *name);
void markTaskComplete(int index, Task* tasks);

#endif
