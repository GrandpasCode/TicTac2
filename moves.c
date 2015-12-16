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
** |  moves.c:  move routines for my game                                  | **
** |                                                                       | **
** +-----------------------------------------------------------------------+ */

#include <stdio.h>
#include <stdlib.h>
#include "tictac2.h"
#include "moves.h"
#include "screen.h"
#include "ai.h"
/*
** getmove(player):  get's a move from a player and put's it on field 
**  actually this routines just calls getmove_xx; where xx is what status is.
*/
void getmove(player p, char *field)
{
  switch(p.status)  {
  case HUMAN_YOU:  getmove_human_you(p, field);  break;
  case CPU:        getmove_cpu(p, field);  break;
  }
} 

/*
** get's a move from (me) using selectspace() or whatever.
** and put it in field[]
*/

void getmove_human_you(player p, char *field)
{
  int tmp;

  tmp=selectspace(field);
  if ( tmp==I_QUIT ) abort();
  else field[ (tmp-1) ] = p.num;

} 

int checkocc(int p1, int p2, int p3, char *s )
{
  if((s[p1]+s[p2]+s[p3])==3)  return 1;
  else if((s[p1]+s[p2]+s[p3])==30)  return 10;
  else return 0;
}

int checkwin(char *field)
{
   int tmp;   

   if ( ( tmp=checkocc(0,1,2,field) ) ) return tmp;
   else if ( ( tmp=checkocc(3,4,5,field) ) ) return tmp;
   else if ( ( tmp=checkocc(6,7,8,field) ) ) return tmp;
   else if ( ( tmp=checkocc(0,3,6,field) ) ) return tmp;
   else if ( ( tmp=checkocc(1,4,7,field) ) ) return tmp;
   else if ( ( tmp=checkocc(2,5,8,field) ) ) return tmp;
   else if ( ( tmp=checkocc(0,4,8,field) ) ) return tmp;
   else if ( ( tmp=checkocc(2,4,6,field) ) ) return tmp;
   else if ( field[0]&&field[1]&&field[2]&&field[3]&&field[4]&&field[5]&&
       field[6]&&field[7]&&field[8] ) return 3;
   else return 0;
}




