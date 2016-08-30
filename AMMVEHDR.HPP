/************************************************************************
* AMMveHdr.hpp - mouse move handler class header                        *
* --------------------------------------------------------------------- *
* Override IHandler class in order to capture mouse move messages for   *
* control windows.  These can be used to generate micro-help requests.  *
* --------------------------------------------------------------------- *
* Overridden methods:                                                   *
*                                                                       *
* Boolean dispatchHandlerEvent - process messages to the window being   *
*                                handled.  The method is overridded in  *
*                                order to intercept the mouse move      *
*                                message specifically.                  *
*                                                                       *
* Protected methods: -------------------------------------------------- *
*                                                                       *
* Boolean motion -               process mouse move message.            *
*                                                                       *
************************************************************************/

#ifndef _AMMVEHDR_HPP
#define _AMMVEHDR_HPP

#include <ihandler.hpp>

class AMouseMoveHandler : public IHandler
{
public:
   Boolean dispatchHandlerEvent( IEvent &evt );

protected:
   virtual Boolean motion( IEvent &evt );

private:
};

#endif /* _AMMVEHDR_HPP_ not defined */
