-----------------------------
Toolbar Demonstration Program
-----------------------------

This program demonstrates a toolbar class comprised of graphical
pushbuttons supporting standard command messages as well as "fly-over"
micro-help via the info area.


Notes:

.  This program was created using CSet++ 2.0 with CTM006 applied to 
   the class library.  This update fixes a number of IGraphicPushButton 
   problems.

.  Templates need to be enabled for the linker as the IQueue class 
   needs them.


Acknowledgements:

This program derives some of its structure from the ICLUI examples
provided in the CSet++ package and from a toolbar example program
written by Stewart Hyde in November of 1993.  Significant help was
received from Compuserve members, especially Hiroshi Tsuji of IBM.


Areas for improvement:

There are a variety of areas that could use some improvement in this
program, and I may eventually get around to fixing them and publishing
another version.  In the meantime you may wish to have a go.

.  The main application should probably be split up into separate
   classes so that it is easier to customize.

.  The toolbar could use some enhancements, like a button-two pop-up 
   that allows it to be moved or customized.

.  The mechanism for communicating the "micro-help" message id to the
   toolbar and the info area is clumsy.  Perhaps an atom table entry
   is a better way to handle this.

.  The menu bar should have fly-over micro-help just like the toolbar 
   has.  An AMenuBar class is needed here.

.  The pushbuttons don't quite look right after they are pushed.  The
   graphics on top may be too big for the current implementation.

.  The toolbar should allow a height/width to be specified in its
   constructor rather than having the size hard-coded.

.  Error-handling is almost non-existent.

Enjoy
Barry Lay
CIS: 72242, 3326

