/************************************************************************
* AMHlpHdr.hpp - micro-help request message class header                *
* --------------------------------------------------------------------- *
* Override IHandler class in order to provide support for a micro-help  *
* request message to be sent from a control to the frame window.  This  *
* message has a user-defined id with two parameters.  The first para-   *
* meter is the control id, and the second is a pointer to the control   *
* window.                                                               *
* --------------------------------------------------------------------- *
* Overridden methods:                                                   *
*                                                                       *
* Boolean dispatchHandlerEvent - process messages to the window being   *
*                                handled.  The method is overridded in  *
*                                order to intercept the micro-help      *
*                                message specifically.                  *
*                                                                       *
* New methods: -------------------------------------------------------- *
*                                                                       *
* void setMessageId -            set the message id for the micro-help  *
*                                request.  This number is added to      *
*                                WM_USER to avoid interference with PM. *
*                                                                       *
* Protected methods: -------------------------------------------------- *
*                                                                       *
* Boolean microHelp -            process micro-help request message     *
*                                from control.                          *
*                                                                       *
************************************************************************/

#ifndef _AMHLPHDR_HPP
#define _AMHLPHDR_HPP

#include <ihandler.hpp>

class AMicroHelpHandler : public IHandler
{
public:
   Boolean dispatchHandlerEvent( IEvent &evt );

   void setMessageId( unsigned long id );

protected:
   virtual Boolean microHelp( IEvent &evt );

private:
   unsigned long messageId;
};

#endif /* _AMHLPHDR_HPP_ not defined */

