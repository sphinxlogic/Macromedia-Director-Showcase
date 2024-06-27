/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	File:		console.h
 *				�1993-1996 metrowerks Inc. All rights reserved
 *	Author:		Berardino E. Baratta
 *
 *	Content:	Interface file to ANSI console package ...
 */

#ifndef __CONSOLE__
#define __CONSOLE__

#include <ansi_parms.h>                     /* mm 970903 */

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Provides an interface to allow users to set argc & argv on the Mac
 */
extern int ccommand(char ***);

/*
 *	The following five functions provide the UI for the console package.
 *	Users wishing to replace SIOUX with their own console package need
 *	only provide the five functions below in a library.
 */

/*
 *	extern short InstallConsole(short fd);
 *
 *	Installs the Console package, this function will be called right
 *	before any read or write to one of the standard streams.
 *
 *	short fd:		The stream which we are reading/writing to/from.
 *	returns short:	0 no error occurred, anything else error.
 */

extern short InstallConsole(short fd);

/*
 *	extern void RemoveConsole(void);
 *
 *	Removes the console package.  It is called after all other streams
 *	are closed and exit functions (installed by either atexit or __atexit)
 *	have been called.  Since there is no way to recover from an error,
 *	this function doesn't need to return any.
 */

extern void RemoveConsole(void);

/*
 *	extern long WriteCharsToConsole(char *buffer, long n);
 *
 *	Writes a stream of output to the Console window.  This function is
 *	called by write.
 *
 *	char *buffer:	Pointer to the buffer to be written.
 *	long n:			The length of the buffer to be written.
 *	returns short:	Actual number of characters written to the stream,
 *					-1 if an error occurred.
 */

extern long WriteCharsToConsole(char *buffer, long n);

/*
 *	extern long ReadCharsFromConsole(char *buffer, long n);
 *
 *	Reads from the Console into a buffer.  This function is called by
 *	read.
 *
 *	char *buffer:	Pointer to the buffer which will recieve the input.
 *	long n:			The maximum amount of characters to be read (size of
 *					buffer).
 *	returns short:	Actual number of characters read from the stream,
 *					-1 if an error occurred.
 */

extern long ReadCharsFromConsole(char *buffer, long n);

/*
 *	extern char *__ttyname(long fildes);
 *
 *	Returns the name of the terminal associated with the file id.  The unix.h
 *	function ttyname calls this function (we need to map the int to a long for
 *	size of int variance).
 *
 *	long filedes:	The file stream's id.
 *	returns char *:	A pointer to the file's name (static global data)
 */

extern char *__ttyname(long fildes);

/*
*
*    int kbhit()
*
*    returns true if any keyboard key is pressed withoug retrieving the key
*    used for stopping a loop by pressing any key
*/
int kbhit(void);

/*
*
*    int getch()
*
*    returns the keyboard character pressed when an ascii key is pressed  
*    used for console style menu selections for immediate actions.
*/
int getch(void);

#ifdef __cplusplus
}	
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
 * mm 970903     Added include of ansi_parms.h to allow compilation without prefix file
*/
