#include "main1.h"

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
    mvprintw((row/2) + i,
             (col - strlen(collections[cIndex].tasks[i].task))/2,
             "%s",
             collections[cIndex].tasks[i].task);
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
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, row, col);
  drawCMenu(cIndex);
  printw("%d", cLength);
  printw("%d", cIndex);
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
        mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
        getstr(name);
        addTaskToCollection(cIndex, name, collections);
        noecho();
      break;
      case 'c':
        echo();
        clear();
        refresh();
        mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
        getstr(name);
      addCollection(name, &collections);
        noecho();
      break;
      case 10:
        tIndex = 0;
        drawTMenu(tIndex, collections, cIndex);
        printw("%d", collections[cIndex].taskCount);
        printw("%d", tIndex); 
        printw("%d", cIndex);
        while((t = getch()) != 'q') {
          switch(t) {
            case KEY_DOWN:
              printw("Breakpoint");
              if (tIndex < collections[cIndex].taskCount - 1) {
                tIndex++;
          }
            break;
            case KEY_UP:
              if (tIndex > 0) {
            tIndex--;
          }
            break;
            case 10:
              markTaskComplete(tIndex, collections[cIndex].tasks);
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


