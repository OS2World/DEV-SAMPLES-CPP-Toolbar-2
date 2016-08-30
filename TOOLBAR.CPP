/************************************************************************
* Toolbar.cpp - demonstration program class implementation              *
* --------------------------------------------------------------------- *
* Demonstrate a toolbar class and simple graphical display.             *
*                                                                       *
* Written by: Barry Lay                                                 *
* Date:       16 September 1994                                         *
*                                                                       *
************************************************************************/

#include <iapp.hpp>                     //IApplication Class
#include <istattxt.hpp>                 //IStaticText Class
#include <istring.hpp>                  //IString Class
#include <ibmpctl.hpp>                  //IBitmapControl Class
#include <iinfoa.hpp>
#include <ifont.hpp>

#define INCL_WIN
#define INCL_GPIPRIMITIVES
#include <os2.h>

#include "atimehdr.hpp"
#include "amhlphdr.hpp"
#include "atoolbar.hpp"
#include "ainfoa.hpp"
#include "toolbar.hpp"
#include "toolbar.h"


lineSegment::lineSegment( IPoint start, IPoint end, IColor colour ) :
   lineStart( start ),
   lineEnd( end ),
   lineColour( colour )
{} /* end lineSegment::lineSegment( ... ) */

/* ---------------------
   private member access
   --------------------- */

void lineSegment::setStart( IPoint start )
{
   lineStart = start;
}  /* end lineSegment::setStart( ... ) */

void lineSegment::setEnd( IPoint end )
{
   lineEnd = end;
}  /* end lineSegment::setEnd() */

void lineSegment::setColour( IColor colour )
{
   lineColour = colour;
}  /* end lineSegment::setColour() */

IPoint lineSegment::start()
{
   return lineStart;
}  /* end lineSegment::start() */

IPoint lineSegment::end()
{
   return lineEnd;
}  /* end lineSegment::end() */

IColor lineSegment::colour()
{
   return lineColour;
}  /* end lineSegment::colour() */

/* -----------------------------------------------------
   draw the line segment in the given presentation space
   ----------------------------------------------------- */

Boolean lineSegment::draw( IPresSpaceHandle hps )
{
   if( !GpiSetColor(hps, lineColour.index()) )
      return false;
   POINTL s = lineStart.asPOINTL();
   POINTL e = lineEnd.asPOINTL();
   if( !GpiMove(hps, &s) )
      return false;
   return GpiLine( hps, &e );
}  /* end lineSegment::draw( ... ) */


/* -----------------------
   main application window
   ----------------------- */

MainWin::MainWin( unsigned long windowId )
    : IFrameWindow ( IFrameWindow::defaultStyle() | IFrameWindow::menuBar,
      windowId )
{
   currentId = 0;
   setupMenuBar( windowId );
   setupInfoArea();
   setupClient();
   createToolBar();

   setFocus();
   show();

   /* set up flashing lines */

   setTimeout( DRAW_TIMEOUT );
   ATimeHandler::handleEventsFor( this );

} /* end MainWin::MainWin( ... ) */


MainWin::~MainWin()
{
   destroyToolBar();
   destroySideBar();
   ATimeHandler::stopHandlingEventsFor( this );
   AMicroHelpHandler::stopHandlingEventsFor( this );
}  /* end MainWin::~MainWin() */


void MainWin::setupMenuBar( unsigned long windowId )
{
   menuBar=new IMenuBar( windowId, this );
   fToolBarActive = false;
   fSideBarActive = false;
   ICommandHandler::handleEventsFor( this );
} /* end MainWin::setupMenuBar( ... ) */


void MainWin::setupClient()
{
   clientWindow = new ICanvas( WND_CANVAS, this, this );
   clientWindow->setAutoDeleteObject();
   currentColour = new IColor( IColor::white );
   clientWindow->setColor( ICanvas::background, *currentColour );
   setClient( clientWindow );
   IPaintHandler::handleEventsFor( clientWindow );
   IResizeHandler::handleEventsFor( clientWindow );

   srand( 17 );
   targetLines = NUM_LINES;
   numLines = 0;
}  /* end MainWin::setupClient() */


void MainWin::setupInfoArea()
{
   infoArea = new AInfoArea( this );
   infoArea->setInactiveText( MICRO_DEFAULT );
   infoArea->setHelpId( MICRO_HELP_MSG );
   setExtensionSize( infoArea, (int)IFont(infoArea).maxCharHeight() );
}  /* end MainWin::setupInfoArea() */


void MainWin::createToolBar()
{
   if (!fToolBarActive)
   {
      myToolBar = new AToolBar( WND_BAR, this );
      myToolBar->setMessageId( MICRO_HELP_MSG );

      myToolBar->addButton( TBS_1 );
      myToolBar->addButton( TBS_2 );
      myToolBar->addButton( TBS_3 );
      myToolBar->addButton( TBS_4 );
      myToolBar->addSpace( 10 );
      myToolBar->addButton( TBL_1 );
      myToolBar->addButton( TBL_2 );
      myToolBar->addSpace( 10 );
      myToolBar->addButton( TBB_1 );
      myToolBar->addButton( TBB_2 );

      addExtension( myToolBar, IFrameWindow::aboveClient,
         (int)myToolBar->minimumSize().height() );
      fToolBarActive = true;
   }
}  /* end MainWin::createToolBar() */


void MainWin::destroyToolBar()
{
   if (fToolBarActive)
   {
      removeExtension( myToolBar );
      delete myToolBar;
      fToolBarActive = false;
   }
   setFocus();
}  /* end MainWin::destroyToolBar() */


void MainWin::createSideBar()
{
   if ( !fSideBarActive )
   {
      mySideBar = new AToolBar( WND_SIDE, this, 
         ISetCanvas::verticalDecks | ISetCanvas::packTight | 
         ISetCanvas::topAlign | ISetCanvas::centerAlign |
         IWindow::visible );
      myToolBar->setMessageId( MICRO_HELP_MSG );

      myToolBar->addButton( TBS_1 );
      myToolBar->addButton( TBS_2 );
      myToolBar->addButton( TBS_3 );
      myToolBar->addButton( TBS_4 );
      myToolBar->addSpace( 10 );
      myToolBar->addButton( TBL_1 );
      myToolBar->addButton( TBL_2 );
      myToolBar->addSpace( 10 );
      myToolBar->addButton( TBB_1 );
      myToolBar->addButton( TBB_2 );

      addExtension( mySideBar,IFrameWindow::leftOfClient,
         (int)mySideBar->minimumSize().width() );
      fSideBarActive = true;
   }
}  /* end MainWin::createSideBar() */


void MainWin::destroySideBar()
{
   if ( fSideBarActive )
   {
      removeExtension( mySideBar );
      delete mySideBar;
      fSideBarActive = false;
   }
   setFocus();
}  /* end MainWin::destroySideBar() */


Boolean MainWin::command(ICommandEvent& cEvent)    //Define command member function
{
   switch ( cEvent.commandId() )
   {
   case MI_HALF:                    /* slow timer down by half */
   case TBS_1:
      if ( timeout() == 0 ) {
         setTimeout( oldTime );
      } else {
         setTimeout( timeout() * 2 );
      } /* endif */
      break;
   case MI_STOP:                    /* stop timer */
   case TBS_2:
      if ( timeout() != 0 ) {
         oldTime = timeout();
         setTimeout( 0 );
      } /* endif */
      break;
   case MI_GO:                      /* restart timer */
   case TBS_3:
      if ( timeout() == 0 ) {
         setTimeout( oldTime );
      } /* endif */
      break;
   case MI_TWICE:                   /* speed timer up twice */
   case TBS_4:
      if ( timeout() == 0 ) {
         setTimeout( oldTime );
      } else {
         setTimeout( timeout() / 2);
      } /* endif */
      break;

   case MI_LESS:                    /* reduce number of lines */
   case TBL_1:
      if ( targetLines > 1 ) {
         targetLines--;
      } /* endif */
      break;
   case MI_MORE:                    /* increase number of lines */
   case TBL_2:
      targetLines++;
      break;

   case MI_BLACK:                   /* black background */
   case TBB_1:
      *currentColour = IColor::black;
      clientWindow->setColor( ICanvas::background, *currentColour );
      clientWindow->refresh();
      break;
   case MI_WHITE:                   /* white background */
   case TBB_2:
      *currentColour = IColor::white;
      clientWindow->setColor( ICanvas::background, *currentColour );
      clientWindow->refresh();
      break;

   default:
      return false;
   }                        
   return true;
}  /* end Toolbar::command( ... ) */


Boolean MainWin::paintWindow( IPaintEvent &evt )
{
   evt.clearBackground( *currentColour );
   lines.removeAll();
   numLines = 0;
   return true;
}  /* end MainWin::paintWindow( ... ) */


Boolean MainWin::windowResize( IResizeEvent &evt )
{
   clientWindow->refresh();
   return true;
}  /* end MainWin::windowResize( ... ) */


Boolean MainWin::tick( IEvent &evt )
{
   IPresSpaceHandle  hps( client()->presSpace() );
   unsigned long     xLine, yLine;
   unsigned long     nStart, nEnd, nOther;
   IColor            colour( IColor::white );
   IColor            colours[NUM_COLOURS] =
   {
      IColor::blue,     IColor::red,       IColor::pink,     IColor::green,
      IColor::cyan,     IColor::yellow,    IColor::darkBlue, IColor::darkRed,
      IColor::darkPink, IColor::darkGreen, IColor::darkCyan, IColor::brown
   };
   lineSegment       line;

   IPoint   start;
   IPoint   end;

   IRectangle bounds = clientWindow->rect();
   yIncr = bounds.height() / 21.0;
   xIncr = bounds.width() / 21.0;

   GpiSetMix( hps, FM_XOR );

   if ( numLines >= targetLines ) {
      lines.dequeue( line );
      line.draw( hps );
      numLines--;
   } /* endif */

   if ( numLines >= targetLines ) {
      client()->releasePresSpace( hps );
      return true;
   } /* endif */

   nStart = rand() * 12 / RAND_MAX + 1;
   nEnd = rand() * (15 - nStart) / RAND_MAX + nStart + 6;
   nOther = rand() * 18 /RAND_MAX + 2;
   if( rand() * 2 / RAND_MAX == 0 )
   {
      xLine = xIncr * nStart;
      yLine = yIncr * nOther;
      start = IPoint( xIncr * nStart, yIncr * nOther );
      end = IPoint( xIncr * nEnd, yIncr * nOther );
   }
   else
   {
      xLine = xIncr * nOther;
      yLine = yIncr * nStart;
      start = IPoint( xIncr * nOther, yIncr * nStart );
      end = IPoint( xIncr * nOther, yIncr * nEnd );
   }

   colour = colours[rand() * NUM_COLOURS / RAND_MAX];
   line = lineSegment( start, end, colour );
   line.draw( hps );
   numLines++;
   lines.enqueue( line );

   client()->releasePresSpace( hps );
   return true;
}  /* end MainWin::tick( ... ) */


void main()
{
  MainWin mainWindow( WND_MAIN );
  IApplication::current().run();
} /* end main */

