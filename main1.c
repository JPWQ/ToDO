#include "main1.h"

int main() {
  int row, col;
  Collection* collections = NULL;
  addCollection("Daily", &collections);
  addCollection("Weekly", &collections);
  getmaxyx(stdscr, row, col);

  initscr();

  nListCollections(collections, row, col);
  getch();
  endwin();

  return 0;
}
