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
** |  ai.c:  ai routines for tictac2                                       | **
** |  Ian Singh. '95 (am256@freenet.carleton.ca)                           | **
** +-----------------------------------------------------------------------+ */

#include <stdio.h>
#include <stdlib.h>
#include "tictac2.h"
#include "ai.h"
#include "moves.h"

int defense(char *field);

/* okay, here's the computer strategy.  first it sees if it can win by
   one move, if it can it will.  If it can't it will look to see if the
   opponent can win by one move only.  If it sees that it will block his
   move.  If it can't do either of those it will then try to set itself
   up for a win.  
*/

/* +------------------------------------------------------+ 
   | edit this to make the computer change it's moves...  | 
   | be careful.  Only put numbers between 0 and 8        |
   +------------------------------------------------------+  */

int computer_moves[]={ 4,0,8,2,6,3,5,7,1 };

int wins[]={ 0,1,2, 1,2,0, 0,2,1, 3,4,5, 4,5,3, 3,5,4, 6,7,8, 7,8,6, 6,8,7,
0,3,6, 3,6,0, 0,6,3, 1,4,7, 4,7,1, 1,7,4, 2,5,8, 5,8,2, 2,8,5, 
0,4,8, 4,8,0, 0,8,4, 2,4,6, 4,6,2, 2,6,4 };
  
int getmove_cpu(player p, char *field)
{
  int i;

   /* offense: try for a one-move win */
   for ( i=0; i<72; i+=3 )
     if ( field[wins[i]]+field[wins[i+1]]==20 )
        if ( !field[wins[i+2]] )  {
          field[wins[i+2]]=p.num;
          return 1;
        }

  /* defense: block probable wins */
  for ( i=0; i<72; i+=3 )
    if ( field[wins[i]]+field[wins[i+1]]==2 )
      if ( !field[wins[i+2]] )  {
        field[wins[i+2]]=p.num;
        return 1;
      }



    /* offense: your average-every day move :-) */
    for ( i=0; i<9; i++ )
      if ( !field[computer_moves[i]] ) {
        field[computer_moves[i]]=p.num;
        return 1;
      }

    return 0;		/* something terrible has happened. */
       
}
