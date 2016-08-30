/************************************************************************
* AToolBar.hpp - toolbar class header                                   *
* --------------------------------------------------------------------- *
* Override ISetCanvas in order to provide a toolbar composed of         *
* graphical pushbuttons.  Support is provided for command actions as    *
* well as "fly-over" micro-help for the buttons.                        *
* --------------------------------------------------------------------- *
* New methods:                                                          *
*                                                                       *
* void setMessageId -   set the message id for the micro-help request   *
*                       to be sent to the frame window.  This should be *
*                       the same as the id set for the AInfoArea.       *
*                                                                       *
* Boolean addButton -   add a button to the toolbar, based on the       *
*                       resource id.                                    *
*                                                                       *
* Boolean addButtons -  add multiple buttons to the toolbar, based on   *
*                       an array of resource ids and a count.           *
*                                                                       *
* Protected methods: -------------------------------------------------- *
*                                                                       *
* Boolean motion -      overridden from AMouseMoveHandler class to      *
*                       intercept mouse move messages for buttons.      *
*                                                                       *
************************************************************************/

#ifndef _ATOOLBAR_HPP_
#define _ATOOLBAR_HPP_

#include <isetcv.hpp>

#include "ammvehdr.hpp"

#define TOOLBAR_TEXT 9999

class AToolBar : public ISetCanvas, 
                 public AMouseMoveHandler
{
public:
   AToolBar( unsigned long windowId, IWindow *owner );
   AToolBar( unsigned long windowId, IWindow *owner, const Style style );

   void setMessageId( unsigned long id );
   Boolean addButton( unsigned long id );
   Boolean addButtons( unsigned long ids[], unsigned long count );
   Boolean addSpace( unsigned long size );

protected:
   virtual Boolean motion( IEvent &evt );

private:
   unsigned long messageId;
};

#endif /* _ATOOLBAR_HPP_ not defined */

