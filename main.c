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
** |				       	       	       	       	       	   | **
** |  main.c:  well, main stuff.					   | **
** |                                                                       | **
** +-----------------------------------------------------------------------+ */

#include <stdio.h>
#include <ncurses/ncurses.h>
#include "tictac2.h"
#include "screen.h"
#include "moves.h"

void usage_exit();
void show_gnu_license();

void main(int argc, char *argv[] )
{
   int gameover=0,i;
   player player1 = { HUMAN_YOU, 1 };
   player player2 = { UNDEFINED, 10 };
   char field[9] = {0,0,0,0,0,0,0,0,0}; 
   char s[50];

   if ( argc<2 )  usage_exit(); 
   if ( !strcasecmp(argv[1],"me") 
        || !strcasecmp(argv[1],"-me") ) player2.status=HUMAN_YOU;
   else if ( !strcasecmp(argv[1],"cpu")
        || !strcasecmp(argv[1],"-cpu") ) player2.status=CPU;
   else {
     /* multi-user initalization stuff goes here... */
   }

   setup_terminal_stuff(); 

   mvaddstr(6,35,"Playing with:");
   attrset(A_STANDOUT); 
   switch(player2.status)  {
   case HUMAN_YOU: mvaddstr(6,35+14,"yourself!");  break;
   case CPU:       mvaddstr(6,35+14,"mr. computer.");  break;
   case HUMAN_THEM: mvaddstr(6,35+14,"someone else.");  break;
   }

   while (1)  {
     getmove(player1, field);  
     refresh_board(field);
     if ( gameover=checkwin(field) ) break;  
     getmove(player2, field);  
     refresh_board(field);
     if ( gameover=checkwin(field) )  break; 
   
   }
   if ( gameover==3 )
     sprintf(s,"Nobody won... you both must suck...");
   else if ( gameover==1 )
     sprintf(s,"You won.. you rule.. %d",gameover);
   else if ( gameover==10 )
     sprintf(s,"you didn't win... you suck :-) %d",gameover); 
   center(23,0,79,s);
   center(24,0,79,"Press any key to Leave...");
   getch();
   kill_terminal_stuff();
   show_gnu_license();
   
}

void usage_exit()
{
  fprintf(stderr,"usage: tictac2 user [tty]\n"
"where user is one of:  me          -- play against your self\n"
"                       cpu         -- play against computer\n" 
"                       user        -- play against another user[doesn't work]\n");
  exit(1);
}

void show_gnu_license()
{
char gnu[]=""
"\n\nTicTac2:  Simple TicTacToe two-player game against another user or cpu.\n"
"Copyright (c) 1995 Ian Singh\n"                            
"\n"                                                                          
"This program is free software; you can redistribute it and/or modify it\n"  
"under the terms  of the  GNU General Public License as published by the\n"  
"Free Software Foundation;  either version 2 of the License, or (at your\n"  
"option) any version later.\n"                                               
"\n"                                                                         
"This program is distriubted in the hope that it  will  be  useful,  but\n"  
"WITHOUT   ANY   WARRANTY;   without   even   the  implied  warranty  of\n"  
"MERCHANTABILITY or FITNESS FOR  A  PARTICULAR  PURPOSE.   See  the  GNU\n"  
"General Public License for more details.\n"                                 
"\n"                                                                         
"You should have received a copy of the GNU General Public License along\n"  
"with  this  program;   if not,  write  to the Free Software Foundation,\n"  
"Inc.,  675 Mass Ave, Cambridge, MA 02139, USA.\n"                          
"\n"                                                                        
"  Ian Singh                           Ian Singh\n"                            
"  am256@freenet.carleton.ca           3G Arnold Dr.\n"                        
"                                      Nepean, Ontario\n"                   
"                                      K2H 6V6\n\n"
"Have a nice day...";                              

puts(gnu);
}
