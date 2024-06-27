/*==========================================================================\
|                                                                           |
|                   Copyright (c) 1994-1998, Macromedia, Inc.               |
|                                                                           |
|	You may utilize this source file to create and compile object code for 	|
|	use within products you may create.  THIS CODE IS PROVIDED "AS IS", 	|
|	WITHOUT WARRANTY OF ANY KIND, AND MACROMEDIA DISCLAIMS ALL IMPLIED 		|
|	WARRANTIES INCLUDING, BUT NOT LIMITED TO, MERCHANTABILITY, FITNESS FOR A|
|	PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT WILL MACROMEDIA BE |
|	LIABLE TO YOU FOR ANY CONSEQUENTIAL, INDIRECT OR INCIDENTAL DAMAGES 	|
|	ARISING OUT OF YOUR USE OR INABILITY TO USE THIS CODE.					|
|                                                                           |
\==========================================================================*/

#ifndef	NO_PRAGMA_ONCE
#pragma	once
#endif

/****************************************************************************
/ Filename
/   $Workfile: drixlngo.h $
/
/ Version:
/   $Revision: 2 $
/
/ Purpose
/	Director Lingo Xtra Inferfaces
/
/ Notes
/
/ Modification History
/	$Log: /Xtras/Include/drixlngo.h $
/   
/   2     6/23/99 11:54 AM Greggy
/   Checkin to synchronize revision numbers.
/   
/   6     10/19/98 11:25 AM Mroeder
/   Changed header from "Confidential" to "You may use..." because these
/   files are in the XDK. Updated copyright notice to cover 1998. 
/   
/   5     2/03/98 10:59a Greggy
/   DP header files now conform with the IML standard. Fixed up guard tag
/   and sequence of #include w.r.t. extern "C".
/   
10dec96 dws Add #error if mmixscrp.h already included.
 3mar96 dac Use AccessArgByIndex() instead of GetArgByIndex()
29feb96 dac check MACINTOSH def in addition to MWERKS.  More comments.
27nov95 dac some clean-up
19jul95 dac split intf. out into IMoaDrUtils, IMoaDrPlayer, IMoaDrMovie;
			move to DRISERVC.H
01may95	ARW	mem_* -> Mem->*
19apr95	JT	Created.
****************************************************************************/


#ifndef	DRIXLNGO_H
#define	DRIXLNGO_H


#include "driservc.h"


#ifdef _H_mmixscrp
#error Don't include both mmixscrp.h and drixlngo.h.
#endif


#ifdef	__cplusplus
extern "C" {
#endif


#if defined( MACINTOSH ) && defined( __MWERKS__ ) && !defined( powerc )
	#pragma push
	#pragma pointers_in_D0
#endif


/*
------------------------------------------------------------------------------

Interface for	IMoaDrXLingo

------------------------------------------------------------------------------
*/

/*---------------------------------------------------------------------------
/ Function: Call
/      Called to dispatch a method of the Lingo Xtra.
/
/ Entry:
/
/	callPtr =
/		xinst 			instance of xobject: reserved.
/		methodFlags		reserved
/		methodSelector 	method index. Zero is first one.
/		resultValue		slot for method result
/		nargs			Number of arguments passed to instance, instance
/							included (nargs always >= 1)
/		pArgs 			Pointer to array of args.  Use GetArgByIndex(), below,
/							to access.
/	
/ Exit:
/
/		callPtr->resultValue set to result (if any)
/
/   	Valid return error codes:
/
/			kMoaErr_NoErr				method call successful
/		    kMoaMmErr_ArgOutOfRange		method selector out of range
/			kMoaErr_OutOfMem			method call failed due to mem err
/			kMoaMmErr_InternalError		method call failed due to
/										 internal err
/			kMoaMmErr_ValueTypeMismatch value supplied for "any"-type
/										  argument not supported by call
/			
/--------------------------------------------------------------------------*/


/* This must be the same GUID as IID_IMoaMmXScript. */
/* IID_IMoaDrXLingo: AC401FB60001F9B000000800072C6326 */
DEFINE_GUID(IID_IMoaDrXLingo, 0xAC401FB6L, 0x0001, 0xF9B0, 0x00, 0x00, 0x08,
				0x00, 0x07, 0x2C, 0x63, 0x26);
				

/* IMoaDrXLingo Interface definition */

#undef INTERFACE
#define INTERFACE IMoaDrXLingo

DECLARE_INTERFACE_(IMoaDrXLingo, IMoaUnknown)

/* Description
<p>
<tt>IMoaDrXLingo </tt>is the interface for Lingo Xtras.  Lingo Xtras provide
the mechanism for defining new Lingo handlers, including global handlers,
parent handlers, and child handlers.  There is only one method in this
interface, <tt>Call()</tt>.<p>
<p>
For more on implementing <tt>IMoaDrXLingo</tt>, see the chapter "Lingo Xtras"
in the <i>Development Guide</i> document.  <p>
*/

{
	STD_IUNKNOWN_METHODS
	
	STDMETHOD(Call)(THIS_
		PMoaDrCallInfo callPtr)  /* Pointer to a <tt>MoaDrCallInfo</tt>
structure */
		PURE;

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=247><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><TT>M</TT>ethod call successful
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=247><TT>kMoaMmErr_ArgOutOfRange</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><TT>M</TT>ethod selector out of
range
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=247><TT>kMoaErr_OutOfMem</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><TT>M</TT>ethod call failed due
to memory error
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=247><TT>kMoaMmErr_InternalError</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><TT>M</TT>ethod call failed due
to internal error
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=247><TT>kMoaMmErr_ValueTypeMismatch</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><TT>V</TT>alue supplied for
<TT>&quot;any&quot;</TT>-type argument not supported
</TD></TR>
</TABLE>
*/

/* Description
<p>
Performs the call specified by the Lingo Xtra.  Use the <tt>methodSelector
</tt>member of the <tt><i>callPtr </i></tt>structure to determine the Lingo
command being called.  <p>
<p>
The <tt>MoaDrCallInfo</tt> structure <tt><i>callPtr</i></tt> contains
information about the method being called and the arguments supplied with the
call.  Lingo Xtras implement this method with a case statement based on the
<tt>methodSelector</tt> field of the call info structure, each case being the
C-enumeration name of one of the handlers implemented.  The code within the
case represents the Xtras response to that particular handler.  <p>
*/

};

typedef IMoaDrXLingo FAR * PIMoaDrXLingo;



#if defined( MACINTOSH ) && defined( __MWERKS__ ) && !defined( powerc )
	#pragma pop
#endif

/*---------------------------------------------------------------------------
Convienence macros.

These all assume callPtr is the PMoaDrCallInfo passed to the main entry point
	Call()

 	Access user parameters to the instance, n is the arg count which is
	1-based. pciGetArgByIndex() macro is defined in DRTYPES.H.
	
	By using this macro, you are getting direct access to the argument
	value, so you should not release this value.  It's owned by the calling
	application.
/--------------------------------------------------------------------------*/


#define AccessArgByIndex(n, pValue) pciGetArgByIndex( callPtr, n, pValue )



/* Don't use this one; exists for backward compatibility with older samples
*/
#define GetArgByIndex(n, pValue)	AccessArgByIndex(n, pValue)


#ifdef	__cplusplus
}
#endif


#endif	/* DRIXLNGO_H */
