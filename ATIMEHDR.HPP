/************************************************************************
* ATimeHdr.hpp - timer class header                                     *
* --------------------------------------------------------------------- *
* Override IHandler class in order to provide support for a timer       *
* message.                                                              *
* --------------------------------------------------------------------- *
* Overridden methods:                                                   *
*                                                                       *
* Boolean dispatchHandlerEvent -    process messages to the window      *
*                                   being handled.  The method is       *
*                                   overridden in order to intercept    *
*                                   the timer message specifically.     *
*                                                                       *
* IHandler &handleEventsFor -       start handling timer events for a   *
*                                   specified window.  If the timeout   *
*                                   value has been set start the timer. *
*                                                                       *
* IHandler &stopHandlingEventsFor - stop handling timer events.  If the *
*                                   timer is running stop the timer.    *
*                                                                       *
* New methods: -------------------------------------------------------- *
*                                                                       *
* void setId -                      set the timer id.  If this is not   *
*                                   set and the timer is started, a     *
*                                   value will be selected.             *
*                                                                       *
* unsigned int id -                 return the timer id.  If the timer  *
*                                   id is not set, return zero.         *
*                                                                       *
* void setTimeout -                 set the timer timeout value.  A     *
*                                   value of zero will stop the timer.  *
*                                   A non-zero value after              *
*                                   handleEventsFor() has been invoked  *
*                                   will restart a stopped timer.       *
*                                                                       *
* unsigned int timeout -            return the timeout value.           *
*                                                                       *
* Protected methods: -------------------------------------------------- *
*                                                                       *
* Boolean tick -                    process timer message.              *
*                                                                       *
************************************************************************/

#ifndef _ATIMEHDR_HPP
#define _ATIMEHDR_HPP

#include <ihandler.hpp>
#include <ihandle.hpp>

class ATimeHandler : public IHandler
{
public:
   ATimeHandler();

   Boolean dispatchHandlerEvent( IEvent &evt );
   IHandler &handleEventsFor( IWindow *window );
   IHandler &stopHandlingEventsFor( IWindow *window );

   void  setId( unsigned int id );
   unsigned int id();
   void  setTimeout( unsigned int timeout );
   unsigned int timeout();

protected:
   virtual Boolean tick( IEvent &evt );

private:
   unsigned int   timerId;
   unsigned int   timerDelay;
   Boolean        timerRunning;
   Boolean        generateId;
   IWindowHandle  hwndWindow;
};

#endif /* _ATIMEHDR_HPP_ not defined */
