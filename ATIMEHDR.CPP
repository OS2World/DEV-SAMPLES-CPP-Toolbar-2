/********************************************
* ATimeHdr.cpp - timer class implementation *
********************************************/

#include <ithread.hpp>
#include <iwindow.hpp>

#define INCL_WINTIMER
#define INCL_WINSYS
#include <os2.h>

#include "atimehdr.hpp"

ATimeHandler::ATimeHandler()
{
   timerRunning = false;
   timerDelay = 0;
   timerId = 0;
   generateId = true;
}  /* end ATimeHandler::ATimeHandler() */


/* -------------------------------------
   override event handler setup routines 
   in order to start and stop timers
   ------------------------------------- */

IHandler & ATimeHandler::handleEventsFor( IWindow *window )
{
   if ( window != NULL ) {
      hwndWindow = window->handle();
      if ( timerDelay != 0 ) {
         if ( generateId ) {
            timerId = WinQuerySysValue( HWND_DESKTOP, SV_CTIMERS );
         } /* endif */
         WinStartTimer( (HAB)IThread::current().anchorBlock(),
            hwndWindow, timerId, timerDelay );
      } /* endif */
      timerRunning = true;
   } /* endif */
   return IHandler::handleEventsFor( window );
}  /* end ATimeHandler::handleEventsFor( ... ) */

IHandler & ATimeHandler::stopHandlingEventsFor( IWindow *window )
{
   if ( window ) {
      if ( window->isValid() && window->handle() == hwndWindow ) {
         WinStopTimer( (HAB)IThread::current().anchorBlock(),
            (HWND)window->handle(), timerId );
      timerRunning = false;
      } /* endif */
   } /* endif */
   return IHandler::stopHandlingEventsFor( window );
}  /* end ATimeHandler::stopHandlingEventsFor( ... ) */


/* ----------------------------------------
   allow timer identifier and timeout value
   to be accessed externally
   ---------------------------------------- */

void ATimeHandler::setId( unsigned int id )
{
   if ( !timerRunning && id < TID_USERMAX && id > 0 ) {
      timerId = id;
      generateId = false;
   } /* endif */
}  /* end ATimeHandler::setId( ... ) */

unsigned int ATimeHandler::id()
{
   return timerId;
}  /* end ATimeHandler::id() */

void ATimeHandler::setTimeout( unsigned int timeout )
{
   if ( timeout == 0 && timerDelay != 0 ) {
      WinStopTimer( (HAB)IThread::current().anchorBlock(),
         hwndWindow, timerId );
   } else {
      if ( timerRunning ) {
         if ( generateId ) {
            timerId = WinQuerySysValue( HWND_DESKTOP, SV_CTIMERS );
         } /* endif */
         WinStartTimer( (HAB)IThread::current().anchorBlock(),
            hwndWindow, timerId, timeout );
      } /* endif */
   } /* endif */
   timerDelay = timeout;
}  /* end ATimeHandler::setTimeout( ... ) */

unsigned int ATimeHandler::timeout()
{
   return timerDelay;
}  /* end ATimeHandler::timeout() */


/* ---------------------
   handle WM_TIMER event
   --------------------- */

Boolean ATimeHandler::tick( IEvent &evt )
{
   return false;
}  /* end ATimeHandler::tick( ... ) */

Boolean ATimeHandler::dispatchHandlerEvent( IEvent &evt )
{
   if ( (evt.eventId() == WM_TIMER) && (evt.parameter1() == timerId) ) {
      timerRunning = true;
      return tick( evt );
   } /* endif */
   return false;
}  /* end ATimeHandler::dispatchHandlerEvent( ... ) */

