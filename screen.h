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


#define BOARD_WIDTH   30 
#define BOARD_LENGTH  13
#define BOARD_SIZE    strlen(BOARD)


void writex(int x, int y);
void writeo(int x,int y);
void setup_terminal_stuff()  ;
void kill_terminal_stuff();
void HiLiteSpace( pos cur ) ;
void UnHiLiteSpace( pos cur ) ;
void center(int y, int x1, int x2, char *string); 
void UnHiLiteByNum(int space);
void HiLiteByNum(int space);
int selectspace(char *field);
void refresh_board(char *field);
void WriteXByNum(int space);
void WriteOByNum(int space);
void Pause();


		               		     
		    
