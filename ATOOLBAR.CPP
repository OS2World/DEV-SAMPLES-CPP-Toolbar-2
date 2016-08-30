/*********************************************
* AToolBar.cpp - toolbar implementation file *
*********************************************/

#include <igraphbt.hpp>
#include <istattxt.hpp>

#define INCL_WINMESSAGEMGR
#include <os2.h>

#include "atoolbar.hpp"

AToolBar::AToolBar( unsigned long windowId, IWindow *owner ) :
   ISetCanvas( windowId, owner, owner, 
      IRectangle(IPoint(), ISize( 1, 1 )),
      ISetCanvas::defaultStyle() )
{
   setMargin( ISize() );
   setPad( ISize() );
   setAutoDeleteObject();
   messageId = 0;
}  /* end AToolBar::AToolBar( ... ) */

AToolBar::AToolBar( unsigned long windowId, IWindow *owner, 
   const Style style ) :
   ISetCanvas( windowId, owner, owner,
      IRectangle(IPoint(), ISize( 1, 1 )), style )
{
   setMargin( ISize() );
   setPad( ISize() );
   setAutoDeleteObject();
   messageId = 0;
}  /* end AToolBar::AToolBar( ... ) */


/* ----------------------------------
   allow control parameters to be set
   ---------------------------------- */

void AToolBar::setMessageId( unsigned long id )
{
   messageId = id;
}  /* end AToolBar::setMessageId( ... ) */


/* ---------------------------------------------------
   provide for the addition of controls to the toolbar
   --------------------------------------------------- */

Boolean AToolBar::addButton( unsigned long id )
{
   IGraphicPushButton *button;

   button = new IGraphicPushButton( id, this, this, id,
      IRectangle(), IGraphicPushButton::defaultStyle() | 
      IButton::noPointerFocus | IGraphicPushButton::sizeToGraphic );
   button->setMinimumSize( ISize(20, 20) );
   button->setAutoDeleteObject();
   AMouseMoveHandler::handleEventsFor( button );
   return true;
}  /* end AToolBar::addButton( ... ) */

Boolean AToolBar::addButtons( unsigned long ids[], unsigned long count )
{
   unsigned long i;

   for( i = 0; i < count; i++ ) {
      addButton( ids[i] );
   } /* endfor */
   return true;
}

Boolean AToolBar::addSpace( unsigned long size )
{
   IStaticText *staticText;

   staticText = new IStaticText( TOOLBAR_TEXT, this, this );
   if ( deckOrientation() == ISetCanvas::horizontal ) {
      staticText->setMinimumSize( ISize(size, 20) );
   } else {
      staticText->setMinimumSize( ISize(20, size) );
   } /* endif */
   staticText->setAutoDeleteObject();
   return true;
}  /* end AToolBar::addSpace( ... ) */


/* -------------------------------------------------------------------
   capture mouse movement messages in order to send microhelp requests
   ------------------------------------------------------------------- */

Boolean AToolBar::motion( IEvent &evt )
{
   if ( messageId > 0 ) {
      owner()->postEvent( WM_USER + messageId, 
         evt.window()->id(), (unsigned long)evt.window() );
   } /* endif */
   return false;  /* allow standard processing */
}  /* end AToolBar::motion( ... ) */

