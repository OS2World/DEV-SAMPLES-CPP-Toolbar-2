/*********************************************
* AMMveHdr.cpp - track WM_MOUSEMOVE messages *
*********************************************/

#include <iwindow.hpp>

#define INCL_WININPUT
#include <os2.h>

#include "ammvehdr.hpp"

/* -------------------------
   handle WM_MOUSEMOVE event
   ------------------------- */

Boolean AMouseMoveHandler::motion( IEvent &evt )
{
   return false;
}  /* end AMouseMoveHandler::motion( ... ) */

Boolean AMouseMoveHandler::dispatchHandlerEvent( IEvent &evt )
{
   if ( evt.eventId() == WM_MOUSEMOVE ) {
      return motion( evt );
   }  /* endif */
   return false;
}  /* end AMouseMoveHandler::dispatchHandlerEvent( ... ) */

