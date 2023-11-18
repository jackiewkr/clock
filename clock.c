/* clock.c
 * =======
 * Simple program that displays the current time at the center of the screen
 * using curses. Press Q to exit cleanly.
 *
 * By Jacqueline W.
 */

#include "ascii_chars.h"

#include <ncurses.h>
#include <time.h>
#include <string.h>

/* enter_ncurses()
 * ==============
 * Enters curses mode and sets some input options.
 */
void enter_ncurses( void )
{
        initscr();
        halfdelay( 10 );                //blocks getch() for 1 second
        noecho();                       //don't echo keys pressed to the term 
        curs_set( 0 );                  //hide cursor
}

/* exit_ncurses()
 * =============
 * Resets options changed and exits curses mode.
 */
void exit_ncurses ( void )
{
        nocbreak();
        echo();
        curs_set(1);
        endwin();
}

/* print_ascii_char()
 * ==================
 * Prints a character to the terminal screen at the given row and column
 * starting location.
 * Only prints characters from list [0,1,2,3,4,5,6,7,8,9,:].
 */
void print_ascii_char( char ch, int col, int row )
{
        char valid_chars[11] = "0123456789:";

        if ( strchr( valid_chars, ch ) != NULL )
        {
                char ascii_char[CHAR_HEIGHT][CHAR_WIDTH] = {};

                switch ( ch )
                {
                case '0':
                        memcpy( ascii_char, ascii_0, sizeof(ascii_char) );
                        break;
                case '1':
                        memcpy( ascii_char, ascii_1, sizeof(ascii_char) );
                        break;
                case '2':
                        memcpy( ascii_char, ascii_2, sizeof(ascii_char) );
                        break;
                case '3':
                        memcpy( ascii_char, ascii_3, sizeof(ascii_char) );
                        break;
                case '4':
                        memcpy( ascii_char, ascii_4, sizeof(ascii_char) );
                        break;
                case '5':
                        memcpy( ascii_char, ascii_5, sizeof(ascii_char) );
                        break;
                case '6':
                        memcpy( ascii_char, ascii_6, sizeof(ascii_char) );
                        break;
                case '7':
                        memcpy( ascii_char, ascii_7, sizeof(ascii_char) );
                        break;
                case '8':
                        memcpy( ascii_char, ascii_8, sizeof(ascii_char) );
                        break;
                case '9':
                        memcpy( ascii_char, ascii_9, sizeof(ascii_char) );
                        break;
                case ':':
                        memcpy( ascii_char, ascii_colon, sizeof(ascii_char) );
                        break;
                }

                for ( int i = 0; i < CHAR_HEIGHT; i++ )
                {
                        mvprintw( row + i, col, "%.*s", CHAR_WIDTH, 
                                  ascii_char[i] );
                }
        }
}

int main( void )
{
        enter_ncurses();

        int row, col;
        unsigned int should_close = 0;
        while ( !should_close )
        {
                // get current time
                time_t raw_time;
                struct tm* time_struct;

                time ( &raw_time );
                time_struct = localtime( &raw_time );

                // get terminal dims
                getmaxyx( stdscr, row, col );

                // convert time to string
                char buf[6] = "";
                snprintf( buf, 6, "%02d:%02d", time_struct->tm_hour, 
                          time_struct->tm_min );

                // print string
                for ( int i = 0; i < 5; i++ )
                {
                        int curr_row = (row - CHAR_HEIGHT)/2;
                        int curr_col = ( col - CHAR_WIDTH * 5 )/2 + 
                                       i * (CHAR_WIDTH + CHAR_PADDING);
                        print_ascii_char( buf[i], curr_col, curr_row );
                }

                refresh();
                if( (char)getch() == 'q' )
                {
                        should_close++;
                }
                erase();
        }
        exit_ncurses();
        return 0;
}

