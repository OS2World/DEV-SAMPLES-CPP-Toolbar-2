/************************************************************************
* Toolbar.h - demonstration program for toolbar class                   *
* --------------------------------------------------------------------- *
* Demonstrate a toolbar class and simple graphical display.             *
*                                                                       *
* Written by: Barry Lay                                                 *
* Date:       16 September 1994                                         *
*                                                                       *
************************************************************************/

#define WND_MAIN        5000           // Main Window Id
#define WND_BAR         5001
#define WND_SIDE        5002
#define WND_TEST        5003
#define WND_TEXT        5004
#define WND_CANVAS      5005
#define WND_CLIENT      5006

/* Main application controls */

#define MI_SPEED        6100
#define MI_HALF         6110
#define MI_STOP         6120
#define MI_GO           6130
#define MI_TWICE        6140

#define MI_LINES        6200
#define MI_LESS         6210
#define MI_MORE         6220

#define MI_BACKGROUND   6300
#define MI_BLACK        6310
#define MI_WHITE        6320

/* various other constants */

#define DRAW_TIMEOUT    100UL          // one tenth second between draws

#define MICRO_DEFAULT   7001           // inactive text id
#define MICRO_HELP_MSG  1              // message id of micro help
#define MICRO_TIMEOUT   100UL          // one tenth of a second timeout

#define NUM_LINES       5              // five lines to start
#define NUM_COLOURS     12             // twelve different line colours

/* Button bar bitmaps */

#define TBS_1           8101           // speed control buttons
#define TBS_2           8102
#define TBS_3           8103
#define TBS_4           8104

#define TBL_1           8201           // line control buttons
#define TBL_2           8202

#define TBB_1           8301           // background control buttons
#define TBB_2           8302

