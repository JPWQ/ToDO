#include "main1.h"

extern int cLength;
extern int tLength;
int row, col;
Collection* collections = NULL;

static void drawCMenu(int index) {
  clear();
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

static void drawTMenu(int index){
  clear();
  for (int i = 0; i <tLength; i++) {
    if (i == index) {
      attron(A_REVERSE);
    }
    mvprintw((row/2) + i, (col - strlen(collections[index].tasks[i].task))/2, "%s", collections[index].tasks[i].task);
    if (i == index) {
      attroff(A_REVERSE);
    }
  }
  refresh();
}
int main() {
  volatile int index = 0;
  volatile int tIndex = 0;
  int c, t;
  char name[100];
  addCollection("Daily", &collections);
  addCollection("Weekly", &collections);

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, row, col);
  drawCMenu(index);
  while((c = getch()) != 'q'){
    switch(c) {
      case KEY_DOWN:
        if (index < cLength - 1) {
          index++;
        }
      break;
      case KEY_UP:
        if (index > 0) {
          index--;
        }
      break;
      case 'a':
        echo();
        clear();
        refresh();
        mvprintw((row/2), (col - strlen("Enter A Name: "))/2, "%s", "Enter A Name: ");
        getstr(name);
        addTaskToCollection(index, name, collections);
        noecho();
      break;
      case 10:
        tIndex = 0;
        drawTMenu(tIndex);
        while((t = getch()) != 'q') {
          switch(t) {
            case KEY_DOWN:
              if (tIndex < tLength - 1) {
                tIndex++;
          }
            break;
            case KEY_UP:
              if (tIndex > 0) {
            tIndex--;
          }
            break;
            case 10:
              getch();
            break;
          }
          drawTMenu(tIndex);
        }
      break;
    }
  drawCMenu(index);
  }
  freeCollections(collections);
  endwin();
  return 0;
}


