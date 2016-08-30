/**********************************************
* AInfoA.cpp - info area class implementation *
**********************************************/

#include <ireslib.hpp>
#include <iframe.hpp>

#define INCL_WIN
#include <os2.h>

#include "ainfoa.hpp"

/* --------------------------------------------------
   set up for receiving help messages and timing them
   -------------------------------------------------- */

AInfoArea::AInfoArea( IFrameWindow *frame, unsigned long id )
   : IInfoArea( frame, id )
{
   currentId = 0;
   inactiveId = 0;

   /* set up micro help */

   setMessageId( MICRO_HELP_MSG );
   AMicroHelpHandler::handleEventsFor( frame );
   ATimeHandler::handleEventsFor( this );

}  /* AInfoArea::AInfoArea() */

AInfoArea::~AInfoArea()
{
   ATimeHandler::stopHandlingEventsFor( this );
   AMicroHelpHandler::stopHandlingEventsFor( this );
}  /* AInfoArea::~AInfoArea() */


/* -----------------------
   manage member variables
   ----------------------- */

IInfoArea & AInfoArea::setInactiveText( unsigned long id )
{
   inactiveId = id;
   return IInfoArea::setInactiveText( id );
}  /* AInfoArea::setInactiveText( ... ) */

IInfoArea & AInfoArea::setInactiveText( const IString &string )
{
   inactiveId = 0;
   return IInfoArea::setInactiveText( string );
}  /* AInfoArea::setInactiveText( ... ) */

void AInfoArea::setHelpId( unsigned long id )
{
   AMicroHelpHandler::setMessageId( id );
}  /* AInfoArea::setHelpId( ... ) */


/* ------------------------
   handle external messages
   ------------------------ */

Boolean AInfoArea::microHelp( IEvent &evt )
{
   if ( (long)evt.parameter1() != currentId ) {
      currentId = (long)evt.parameter1();
      if ( currentId == 0 ) {
         setText( inactiveId );
         setTimeout( 0 );
      } else {
         setText( currentId );
         activeWindow = (IWindow *)(unsigned long)evt.parameter2();
         setTimeout( MICRO_TIMEOUT );
      } /* endif */
   } /* endif */
   return true;
}  /* AInfoArea::microHelp( ... ) */

Boolean AInfoArea::tick( IEvent &evt )
{
   IRectangle  win( activeWindow->rect() );
   POINTL      ptlHere;
   IPoint      cursor;

   WinQueryPointerPos( HWND_DESKTOP, &ptlHere );
   cursor = activeWindow->mapPoint( ptlHere,
      HWND_DESKTOP, activeWindow->handle() );
   win = win.moveTo( IPoint(0, 0) );
   if ( !win.contains(cursor) ) {
      setTimeout( 0 );
      currentId = 0;
      setText( inactiveId );
   } /* endif */
   return true;
}  /* AInfoArea::tick( ... ) */

