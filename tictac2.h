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

/*
**  nothing here yet...
**
*/

typedef struct{
  int x,y ;
} pos;

typedef struct {
  int status,num;
}  player;


#define SPACE1 0,0 
#define SPACE2 10,0
#define SPACE3 20,0 

#define SPACE4 0,4
#define SPACE5 10,4
#define SPACE6 20,4

#define SPACE7 0,8
#define SPACE8 10,8
#define SPACE9 20,8

#define I_QUIT 10

#define HUMAN_YOU  1
#define HUMAN_THEM 2 
#define CPU        3
#define UNDEFINED  0


