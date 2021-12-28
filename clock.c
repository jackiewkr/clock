/*
Clock app made to learn C and ncurses.

By Jackie W.

21 dec 21
*/

#include <ncurses.h>
#include <stdbool.h>
#include <time.h>

void enterCurses() {
  initscr();
  keypad(stdscr, TRUE);
  halfdelay(10);
  //nodelay(stdscr,true);
  noecho();
  curs_set(0);
}

void exitCurses() {
  nocbreak();
  echo();
  curs_set(1);
  endwin();
}

void printBigColon(int row, int col,int sec){
  int startCol = (col-17)/2;
  int startRow = (row-5)/2;
  int colOffset = 4*2; //rough column offset
  if (sec % 2 == 0){
    mvprintw(startRow+1,startCol+colOffset+1,"#");
    mvprintw(startRow+3,startCol+colOffset+1,"#");
  }
}

void printBigNum(int num, int pos,int row, int col) {
  /*Prints big ASCII art numbers at a given place
   int num: number to be displayed
   int pos: place for number to be positioned (0-3)*/
  int startCol = (col-17)/2;
  int startRow = (row-5)/2;
  int colOffset = 4*pos; //rough column offset
  if (pos > 1) {
    colOffset = colOffset + 3;
  }
  switch (num) {
  case 0:
    mvprintw(startRow,startCol+colOffset,"###");
    mvprintw(startRow+1,startCol+colOffset,"# #");
    mvprintw(startRow+2,startCol+colOffset,"# #");
    mvprintw(startRow+3,startCol+colOffset,"# #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 1:
    mvprintw(startRow,startCol+colOffset," # ");
    mvprintw(startRow+1,startCol+colOffset,"## ");
    mvprintw(startRow+2,startCol+colOffset," # ");
    mvprintw(startRow+3,startCol+colOffset," #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 2:
    mvprintw(startRow,startCol+colOffset,"###");
    mvprintw(startRow+1,startCol+colOffset,"  #");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"# ");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 3:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"  #");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"  #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 4:
    mvprintw(startRow,startCol+colOffset,  "# #");
    mvprintw(startRow+1,startCol+colOffset,"# #");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"  #");
    mvprintw(startRow+4,startCol+colOffset,"  #");
    break;
  case 5:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"# ");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"  #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 6:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"# ");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"# #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 7:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"  #");
    mvprintw(startRow+2,startCol+colOffset,"  #");
    mvprintw(startRow+3,startCol+colOffset,"  #");
    mvprintw(startRow+4,startCol+colOffset,"  #");
    break;
  case 8:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"# #");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"# #");
    mvprintw(startRow+4,startCol+colOffset,"###");
    break;
  case 9:
    mvprintw(startRow,startCol+colOffset,  "###");
    mvprintw(startRow+1,startCol+colOffset,"# #");
    mvprintw(startRow+2,startCol+colOffset,"###");
    mvprintw(startRow+3,startCol+colOffset,"  #");
    mvprintw(startRow+4,startCol+colOffset,"  #");
    break;
  default:
    printw("%d",num);
  }
}

int main(){
  enterCurses();

  //bool for whether the program should close
  bool loop;
  loop = true;

  int row, col;

  while (loop == 1) {
    //main loop of the program

    //get current time
    time_t rawCurrTime;
    struct tm * currTime;

    time(&rawCurrTime);
    currTime = localtime(&rawCurrTime);

    //get new screen dims
    getmaxyx(stdscr,row,col);

    //calc numbers to be displayed for each pos
    int msb_hour = 0;
    if (currTime->tm_hour > 9) {
      msb_hour = currTime->tm_hour / 10;
    } 
    int lsb_hour = currTime->tm_hour - (msb_hour * 10);

    int msb_min = 0;
    if (currTime->tm_min > 9) {
      msb_min = currTime->tm_min / 10;
    }
    int lsb_min = currTime->tm_min - msb_min *10;
    printBigNum(msb_hour,0,row,col);
    printBigNum(lsb_hour,1,row,col);
    printBigNum(msb_min,2,row,col);
    printBigNum(lsb_min,3,row,col);
    printBigColon(row,col,currTime->tm_sec);

    //refresh the screen
    refresh();
    getch();
    erase();
  }
  exitCurses();
  return 0;
}

