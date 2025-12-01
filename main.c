#include "main.h"

extern int cLength;
volatile int cIndex = 0;
volatile int tIndex = 0;
int row, col;
Collection* collections = NULL;

static void drawCMenu(int index) {
  clear();
  refresh();
  for (int i = 0; i <cLength; i++) {
    if (i == index) {
      attron(A_REVERSE);
    }
    mvprintw((row/2) + i, (col - strlen(collections[i].collection))/2, "%s", collections[i].collection);
    if (i == index) {
      attroff(A_REVERSE);
    }
  }
  refresh();
}

static void drawTMenu(volatile int index, Collection *collections, int cIndex){
  clear();
  refresh();

  if (collections[cIndex].taskCount == 0){
    mvprintw(row/2, col/2 - 5, "%s", "No Tasks");
    refresh();
    return;
  }
  for (int i = 0; i < collections[cIndex].taskCount; i++) {
    if (i == index) {
      attron(A_REVERSE);
    }
    if (collections[cIndex].tasks[i].completed == 1) {
      attron(COLOR_PAIR(1));
    }
    mvprintw((row/2) + i,
             (col - strlen(collections[cIndex].tasks[i].task))/2,
             "%s",
             collections[cIndex].tasks[i].task);
    if ( collections[cIndex].tasks[i].completed == 1) {
      attroff(COLOR_PAIR(1));
    }
    if (i == index) {
      attroff(A_REVERSE);
    }
  }
  refresh();
}

int main() {
  int c, t;
  char name[100];
  addCollection("Daily", &collections);
  addCollection("Weekly", &collections);

  initscr();

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, row, col);
  drawCMenu(cIndex);
  while((c = getch()) != 'q'){
    clear();
    refresh();
    switch(c) {
      case KEY_DOWN:
        if (cIndex < cLength - 1) {
          cIndex++;
        }
      break;
      case KEY_UP:
        if (cIndex > 0) {
          cIndex--;
        }
      break;
      case 'a':
        echo();
        clear();
        refresh();
        mvprintw((row/2) - 1,
                 ((col - (strlen("Add A Task To Collection.") + strlen(collections[cIndex].collection)))/2),
                 "Add A Task To %s Collection.",
                 collections[cIndex].collection);
        mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
        getstr(name);
        addTaskToCollection(cIndex, name, collections);
        noecho();
      break;
      case 'c':
        echo();
        clear();
        refresh();
        mvprintw((row/2) - 1,
                 (col - strlen("Add A New Collection."))/2,
                 "%s",
                 "Add A New Collection.");
        mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
        getstr(name);
      addCollection(name, &collections);
        noecho();
      break;
      case 'd':
        clear();
        refresh();
        if (cLength > 0) {
          deleteCollection(cIndex, collections);
        }
      break;
      case 'e':
        if (cLength > 0) {
          echo();
          clear();
          refresh();
          mvprintw((row/2) - 1,
                   (col - (strlen("Edit The Name Of  Collection.") + strlen(collections[cIndex].collection)))/2,
                   "Edit The Name Of %s Collection.",
                   collections[cIndex].collection);
          mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
          getstr(name);
          editCollection(cIndex, name, &collections);
          noecho();
        }
      break;
      case 10:
        tIndex = 0;
        drawTMenu(tIndex, collections, cIndex);
        while((t = getch()) != 'q') {
          switch(t) {
            case KEY_DOWN:
              if (tIndex < collections[cIndex].taskCount - 1) {
                tIndex++;
          }
            break;
            case KEY_UP:
              if (tIndex > 0) {
            tIndex--;
          }
            break;
            case 'd':
              clear();
              refresh();
              if (collections[cIndex].taskCount > 0){
                deleteTask(tIndex, &collections[cIndex].taskCount, collections[cIndex].tasks);
              }
            break;
            case 'e':
              if (collections[cIndex].taskCount > 0) {
                echo();
                clear();
                refresh();
                mvprintw((row/2) - 1,
                         (col - (strlen("Edit Task .") + strlen(collections[cIndex].tasks[tIndex].task)))/2,
                         "Edit Task %s.",
                         collections[cIndex].tasks[tIndex].task);
                mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
                getstr(name);
                editTask(tIndex, &collections[cIndex].tasks, name);
                noecho();
              }
            break;
            case 10:
              if (collections[cIndex].taskCount > 0){
                markTaskComplete(tIndex, collections[cIndex].tasks);
              }
            break;
          }
          drawTMenu(tIndex, collections, cIndex);
        }
      break;
    } 
  drawCMenu(cIndex);
  }
  freeCollections(collections);
  endwin();
  return 0;
}


