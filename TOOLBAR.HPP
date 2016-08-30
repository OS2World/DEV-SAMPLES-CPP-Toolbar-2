/************************************************************************
* Toolbar.hpp - demonstration program class header                      *
* --------------------------------------------------------------------- *
* Demonstrate a toolbar class and simple graphical display.             *
*                                                                       *
* Written by: Barry Lay                                                 *
* Date:       16 September 1994                                         *
*                                                                       *
************************************************************************/

#include <iframe.hpp>               // IFrameWindow class
#include <icmdhdr.hpp>              // ICommandHandler class
#include <imenubar.hpp>             // IMenuBar class
#include <ipainhdr.hpp>             // IPaintHandler class
#include <isizehdr.hpp>             // IResizeHandler class
#include <iqueue.h>                 // IQueue class

#include "ainfoa.hpp"               // AInfoArea class
#include "atimehdr.hpp"             // ATimeHandler class
#include "amhlphdr.hpp"             // AMicroHelpHandler class
#include "atoolbar.hpp"             // AToolbar class

class lineSegment
{
public:
   lineSegment( IPoint start = IPoint(), IPoint end = IPoint(), 
      IColor colour = IColor::black );

   /* use default destructor, copy, and assignment */

   virtual void   setStart( IPoint start );
   virtual void   setEnd( IPoint end );
   virtual void   setColour( IColor colour );
   virtual IPoint start();
   virtual IPoint end();
   virtual IColor colour();

   draw( IPresSpaceHandle hps );

private:
   IPoint         lineStart;
   IPoint         lineEnd;
   IColor         lineColour;
};

typedef IQueue <lineSegment> lineQueue;

class MainWin : public IFrameWindow,
                public ICommandHandler,
                public IPaintHandler,
                public IResizeHandler,
                public ATimeHandler
{
public:
   MainWin( unsigned long windowId );
   virtual ~MainWin();

   virtual Boolean   command( ICommandEvent& cEvent );

protected:
   virtual void      setupInfoArea();
   virtual void      setupClient();

   virtual void      createToolBar();
   virtual void      destroyToolBar();
   virtual void      createSideBar();
   virtual void      destroySideBar();
   virtual void      setupMenuBar( unsigned long windowId );

   virtual Boolean   paintWindow( IPaintEvent &evt );
   virtual Boolean   windowResize( IResizeEvent &evt );
   virtual Boolean   tick( IEvent &evt );

private:
   ICanvas          *clientWindow;
   AInfoArea        *infoArea;
   IMenuBar         *menuBar;

   Boolean           fToolBarActive;
   AToolBar         *myToolBar;
   Boolean           fSideBarActive;
   AToolBar         *mySideBar;

   unsigned long     currentId;     // current displayed help Id
   IWindow          *activeWindow;  // window with micro help

   IColor           *currentColour; // current line area colour

   unsigned long     xIncr, yIncr;  // space between lines
   unsigned long     numLines;      // number of flashing lines
   unsigned long     targetLines;   // desired number of lines

   lineQueue         lines;         // queue of line segments for display
                                    //  persistance

   unsigned long     oldTime;       // current line draw timeout
};

