/*****************************************************************************.
**  TicTac2:  Simple TicTacToe two-player game against another user or cpu.  **
**  Copyright (c) 1995 Ian Singh                                             **
**                                                                           **
**  This program is free software; you can redistribute it and/or modify it  **
**  under the terms  of the  GNU General Public License as published by the  **
**  Free Software Foundation;  either version 2 of the License, or (at your  **
**  option) any version later.                                               **
**                                                                           **
**  This program is distriubted in the hope that it  will  be  useful,  but  **
**  WITHOUT   ANY   WARRANTY;   without   even   the  implied  warranty  of  **
**  MERCHANTABILITY or FITNESS FOR  A  PARTICULAR  PURPOSE.   See  the  GNU  **
**  General Public License for more details.                                 **
**                                                                           **
**  You should have received a copy of the GNU General Public License along  **
**  with  this  program;   if not,  write  to the Free Software Foundation,  **
**  Inc.,  675 Mass Ave, Cambridge, MA 02139, USA.                           **
**                                                                           **
**  Ian Singh                           Ian Singh                            **
**  am256@freenet.carleton.ca           3G Arnold Dr.                        **
**                                      Nepean, Ontario                      **
**                                      K2H 6V6                              **
.*****************************************************************************/


/* +-----------------------------------------------------------------------+ **
** |  screen.c: 							   | **
** |                                                                       | **
** |  Some screen/curses routines for my game.  			   | **
** +-----------------------------------------------------------------------+ */

#include <ncurses.h>
#include <string.h>
#include "tictac2.h"
#include "screen.h"
#include <unistd.h>
#include <ctype.h>

char  BOARD[] =
".---------+---------+---------,"
"|         |         |         |"
"|         |         |         |"
"|         |         |         |"
"+---------+---------+---------+"
"|         |         |         |"
"|         |         |         |"
"|         |         |         |"
"+---------+---------+---------+"
"|         |         |         |"
"|         |         |         |"
"|         |         |         |"
"`---------+---------+---------'";

pos pos1 = { SPACE1 };
pos pos2 = { SPACE2 };
pos pos3 = { SPACE3 };
pos pos4 = { SPACE4 };
pos pos5 = { SPACE5 };
pos pos6 = { SPACE6 };
pos pos7 = { SPACE7 };
pos pos8 = { SPACE8 };
pos pos9 = { SPACE9 };

int hascolour;

/*
**  writex(x,y):  draw an X somewhere.
**
*/
void writex(int x, int y)
{
  mvaddch(y,x,'\\');            /* that's a \, stupid */
  mvaddch(y,x+4,'/');
  mvaddch(y+1,x+2,'x');
  mvaddch(y+2,x,'/');
  mvaddch(y+2,x+4,'\\');
}

/*
**  writeo(x,y):  draw an O somewhere.
**
*/
void writeo(int x,int y)
{
  mvaddch(y,x,'/');
  mvaddch(y,x+1,'~');
  mvaddch(y,x+2,'~');
  mvaddch(y,x+3,'~');
  mvaddch(y,x+4,'\\');
  mvaddch(y+1,x,'|');
  mvaddch(y+1,x+4,'|');
  mvaddch(y+2,x,'\\');
  mvaddch(y+2,x+1,'_');
  mvaddch(y+2,x+2,'_');
  mvaddch(y+2,x+3,'_');
  mvaddch(y+2,x+4,'/');
}

/*
**  setup_terminal_sutff(); Init/Setup/Draw the terminal screen.
**
*/
void setup_terminal_stuff()  {
  char s;
  int i=0,p=0;

  initscr();
  refresh();
  keypad(stdscr,TRUE);
  nocrmode();
  noecho();
  cbreak();
  for ( i=0;i<BOARD_SIZE;i++ )  {
    addch( BOARD[i] );
    if ( p==BOARD_WIDTH )  { addch('\n'); p=0; }  else { p++; }
  }
  mvaddstr(3,35,"TicTac2");
  attrset(A_REVERSE);
  mvaddstr(4,35,"Version 0.6");
  attrset(A_STANDOUT);
  mvaddstr(5,35,"--------------------");
  mvaddstr(10,35,"Author:");
  mvaddstr(11,35,"Ian Singh (am256@freenet.carleton.ca)");
  
  attrset(A_NORMAL);
}

/*
**
** void kill_terminal_stuff(): end all this stuff properly.
*/
void kill_terminal_stuff() {
 clear();
  endwin();
}

/*
**  HiLiteSpace(pos):  HiLiteASpace by (screen)co-ordinates.
**
*/
void HiLiteSpace( pos cur ) {
  int i;

  attrset(A_STANDOUT);
  for (i=cur.x;i<(cur.x+11);i++)  {
    mvaddch( cur.y, i,   BOARD[ (((BOARD_WIDTH+1)*cur.y)+i) ]  );
    mvaddch( (cur.y+4), i, BOARD[ (((BOARD_WIDTH+1)*(cur.y+4))+i) ]  );
  }
  for (i=cur.y+1;i<(cur.y+4);i++)  {
    mvaddch( i, cur.x,  BOARD[  (((BOARD_WIDTH+1)*i)+cur.x) ] );
    mvaddch( i, cur.x+10, BOARD[  (((BOARD_WIDTH+1)*i)+(cur.x+10)) ] );
  }
  attrset(A_NORMAL);
}

/*
**  UnHiLiteSpace(pos):  UnHiLiteASpace by (screen)co-ordinates.
**
*/ 
void UnHiLiteSpace( pos cur ) {
  int i;

  attrset(A_NORMAL);
  for (i=cur.x;i<(cur.x+11);i++)  {
    mvaddch( cur.y, i,   BOARD[ (((BOARD_WIDTH+1)*cur.y)+i) ]  );
    mvaddch( (cur.y+4), i, BOARD[ (((BOARD_WIDTH+1)*(cur.y+4))+i) ]  );
  }
  for (i=cur.y+1;i<(cur.y+4);i++)  {
    mvaddch( i, cur.x,  BOARD[  (((BOARD_WIDTH+1)*i)+cur.x) ] );
    mvaddch( i, cur.x+10, BOARD[  (((BOARD_WIDTH+1)*i)+(cur.x+10)) ] );
  }
  attrset(A_NORMAL);
}

/*
**  center(x,y):  center *string between x1 and x2 on line y in A_STANDOUT...
**                warning: everything on line y is deleted.
*/
void center(int y, int x1, int x2, char *string) {
  move(y,0);
  clrtoeol();
  attrset(A_STANDOUT);
  mvaddstr(y,((x2-x1)/2)-(strlen(string)/2),string);
  attrset(A_NORMAL);
}

/*
**  UnHiLiteByNum(int):  another one of those lovely unhilight func's.
**                       but this 'cepts a number instead of co-ordinates
**                       whoop-tee-doo.
*/
 
void UnHiLiteByNum(int space)
{

switch(space)  {
case 1:  UnHiLiteSpace(pos1);  break;
case 2:  UnHiLiteSpace(pos2);  break;
case 3:  UnHiLiteSpace(pos3);  break;
case 4:  UnHiLiteSpace(pos4);  break;
case 5:  UnHiLiteSpace(pos5);  break;
case 6:  UnHiLiteSpace(pos6);  break;
case 7:  UnHiLiteSpace(pos7);  break;
case 8:  UnHiLiteSpace(pos8);  break;
case 9:  UnHiLiteSpace(pos9);  break;
               }

}

void WriteXByNum(int space)
{

switch(space)  {
case 1:  writex(pos1.x+3, pos1.y+1);  break;
case 2:  writex(pos2.x+3, pos2.y+1);  break;
case 3:  writex(pos3.x+3, pos3.y+1);  break;
case 4:  writex(pos4.x+3, pos4.y+1);  break;
case 5:  writex(pos5.x+3, pos5.y+1);  break;
case 6:  writex(pos6.x+3, pos6.y+1);  break;
case 7:  writex(pos7.x+3, pos7.y+1);  break;
case 8:  writex(pos8.x+3, pos8.y+1);  break;
case 9:  writex(pos9.x+3, pos9.y+1);  break;
               }

}

void WriteOByNum(int space)
{
switch(space)  {
case 1:  writeo(pos1.x+3, pos1.y+1);  break;
case 2:  writeo(pos2.x+3, pos2.y+1);  break;
case 3:  writeo(pos3.x+3, pos3.y+1);  break;
case 4:  writeo(pos4.x+3, pos4.y+1);  break;
case 5:  writeo(pos5.x+3, pos5.y+1);  break;
case 6:  writeo(pos6.x+3, pos6.y+1);  break;
case 7:  writeo(pos7.x+3, pos7.y+1);  break;
case 8:  writeo(pos8.x+3, pos8.y+1);  break;
case 9:  writeo(pos9.x+3, pos9.y+1);  break;
               }

}

/*
** refresh_board():  draw's all the x'S and o'S.
**
*/
void refresh_board(char *field) 
{
  int i;
  for ( i=0; i<9; i++ )  {
    switch(field[i])  {
      case 1:  WriteXByNum(i+1); break;
      case 10:  WriteOByNum(i+1); break;
    }
  }
  
}

/*
**  HiLiteByNum(int):    another one of those lovely hilight func's.
**                       but this 'cepts a number(1-9) instead of co-ordinates
**                       whoop-tee-doo.
*/
void HiLiteByNum(int space)
{

switch(space)  {
case 1:  HiLiteSpace(pos1);  break;
case 2:  HiLiteSpace(pos2);  break;
case 3:  HiLiteSpace(pos3);  break;
case 4:  HiLiteSpace(pos4);  break;
case 5:  HiLiteSpace(pos5);  break;
case 6:  HiLiteSpace(pos6);  break;
case 7:  HiLiteSpace(pos7);  break;
case 8:  HiLiteSpace(pos8);  break;
case 9:  HiLiteSpace(pos9);  break;
               }

}

void Pause()
{  getch(); 
} 

/* selectspace(void):  use cursor keys to select a space. q to abort/quit.
** RETURNS:            if ok, number of space that was picked. if quit, then
**                     I_QUIT(10).
*/
int selectspace(char *field)
{
  int key,cs=1;

  center(24,0,79,"Use the arrow keys to select a space.");

  HiLiteByNum(1);
  while (1)  {
    key=getch();
    switch ( toupper(key) )  {
    case KEY_LEFT: if(cs-1<1) { beep();  center(24,0,79,"can't go that far");}
                     else { UnHiLiteByNum(cs); cs--; HiLiteByNum(cs); } break;
    case KEY_RIGHT: if(cs+1>9) {beep(); center(24,0,79,"can't go that far"); }
                      else { UnHiLiteByNum(cs); cs++; HiLiteByNum(cs); } break;
    case KEY_UP: if(cs-3<1) { beep(); center(24,0,79,"can't go that far");}
                   else { UnHiLiteByNum(cs); cs-=3; HiLiteByNum(cs); } break;
    case KEY_DOWN: if(cs+3>9) {beep(); center(24,0,79,"can't go that far"); }
                   else { UnHiLiteByNum(cs); cs+=3; HiLiteByNum(cs); } break;
    case '\n': if (field[(cs-1)]){beep();center(24,0,79,"already used");}
               else { UnHiLiteByNum(cs); return (cs); } break;
    case 'Q':  return ( I_QUIT );  break;
    default: beep(); center(24,0,79,"Use yer left and right arrowz to move.");
             break;
    }
  }
}




























