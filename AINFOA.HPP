/************************************************************************
* AInfoA.hpp - info area class header                                   *
* --------------------------------------------------------------------- *
* Override IInfoArea class in order to allow "fly-over" micro-help via  *
* a user message sent from controls to the frame.  The user message is  *
* expected to contain the id of the window in parameter one (used by    *
* the standard IInfoArea processing to get the string to display), and  *
* a pointer to the window which is used by AInfoArea to test for mouse  *
* pointer inclusion in the control after a timeout.                     *
* --------------------------------------------------------------------- *
* Overridden methods:                                                   *
*                                                                       *
* IInfoArea &setInactiveText - set inactive text via a resource id or   *
*                              an IString.  The method is overridden in *
*                              order to capture the id for resetting    *
*                              the text after the mouse leaves the      *
*                              control being monitored.                 *
*                                                                       *
* New methods: -------------------------------------------------------- *
*                                                                       *
* void setHelpId -             set the message id of the user message   *
*                              used to communicate a micro-help request *
*                              from a control.  This number is added to *
*                              WM_USER to prevent interference with PM. *
*                                                                       *
* Protected methods: -------------------------------------------------- *
*                                                                       *
* Boolean microHelp -          overridden from AMicroHelpHandler class  *
*                              to process micro-help request message    *
*                              from control.                            *
*                                                                       *
* Boolean tick -               overridden from ATimeHandler class to    *
*                              process timeout after receipt of micro-  *
*                              help request message.                    *
*                                                                       *
************************************************************************/

#ifndef _AINFOA_HPP
#define _AINFOA_HPP

#include <iinfoa.hpp>
#include "atimehdr.hpp"
#include "amhlphdr.hpp"

#define MICRO_HELP_MSG  1              // message id of micro help
#define MICRO_TIMEOUT   100UL          // one tenth of a second timeout

class AInfoArea : public IInfoArea,
                  public ATimeHandler,
                  public AMicroHelpHandler
{
public:
   AInfoArea( IFrameWindow *frame, unsigned long id = 0 );
   virtual ~AInfoArea();

   virtual IInfoArea & setInactiveText( const IString &string );
   virtual IInfoArea & setInactiveText( unsigned long id );
   virtual void setHelpId( unsigned long id );

protected:
   virtual Boolean tick( IEvent &evt );
   virtual Boolean microHelp( IEvent &evt );

private:
   unsigned long  inactiveId;       // inactive text id
   unsigned long  currentId;        // current displayed help Id
   IWindow       *activeWindow;     // window with micro help
};

#endif /* _AINFOA_HPP_ not defined */

