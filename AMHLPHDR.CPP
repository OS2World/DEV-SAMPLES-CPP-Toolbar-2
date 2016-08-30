/****************************************************************
* AMHlpHdr.cpp - allow micro-help via the UM_MICROHELP message. *
****************************************************************/

#include <iwindow.hpp>

#define INCL_WINMESSAGEMGR
#include <os2.h>           /* get WM_USER definition */

#include "amhlphdr.hpp"


/* --------------------------
   allow message id to be set
   -------------------------- */

void AMicroHelpHandler::setMessageId( unsigned long id )
{
   messageId = id;
}  /* end AMicroHelpHandler::setMessageId( ... ) */


/* ---------------------------
   handle UM_MICROHELP message
   --------------------------- */

Boolean AMicroHelpHandler::microHelp( IEvent &evt )
{
   return false;
}  /* end AMicroHelpHandler::microHelp( ... ) */


Boolean AMicroHelpHandler::dispatchHandlerEvent( IEvent &evt )
{
   if ( evt.eventId() == WM_USER + messageId ) {
      return microHelp( evt );
   }  /* endif */
   return false;
}  /* end AMicroHelpHandler::dispatchHandlerEvent( ... ) */

