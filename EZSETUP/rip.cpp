// EzSetup - an CE app install maker
// Copyright (C) 1998-2001 Scott Ludwig
// scottlu@eskimo.com
// http://www.eskimo.com/~scottlu
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// or visit http://www.gnu.org/copyleft/gpl.html.

/////////////////////////////////////////////////////////////////////////////
// rip.cpp
/////////////////////////////////////////////////////////////////////////////
// This module contains support for communicating errors or messages to a
// developer or tester.
/////////////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "rip.h"
#include <stdio.h>

#if defined(_DEBUG)

char *gpszRipFile;
int giRipLine;

/////////////////////////////////////////////////////////////////////////////
// DoRip
/////////////////////////////////////////////////////////////////////////////

// Turn off c++ exception handler unwind semantics not enabled warning

#pragma warning(disable : 4530)

void __cdecl DoRip(char *pszTitle, char *psz, va_list va)
{
    int idT;
    bool fBeingDebugged;
    static bool gfRipActive = FALSE;

    // If gpszRipFile is not NULL, Format the string
    // "File: name.cpp, Line: nnn, ..."
    // Otherwise, format the string without the File/Line info.

    char szT[256];
    char szT1[128];
    wvsprintf(szT1, psz, va);

    if (gpszRipFile != NULL)
        wsprintf(szT, "\n%s: File: %s, Line: %d. %s\n", pszTitle, gpszRipFile, giRipLine, szT1);
    else
        wsprintf(szT, "%s: %s", pszTitle, szT1);

    // This'll break into the debugger if the debugger is present,
    // otherwise it'll fall through to the message box case.

    OutputDebugString(szT);

    fBeingDebugged = TRUE;
    try {
        _asm {
            int 3;
        }
    } catch (...) {
        fBeingDebugged = FALSE;
    }

    // If we are not being debugged, bring up the message box

    if (fBeingDebugged)
		return;
		
    // Bring up a message box with these options:
    // Abort: terminate app
    // Retry: break
    // Ignore: keep running        

    // We don't want to recurse, which may happen when this message
    // box comes up due to WM_ACTIVATE messages and other being
    // sent back to the app

    if (gfRipActive)
        return;

    gfRipActive = TRUE;
    idT = MessageBox(NULL, strchr(szT, ':') + 2, pszTitle,
			MB_ABORTRETRYIGNORE | MB_SETFOREGROUND);
    gfRipActive = FALSE;

    switch (idT) {
    case IDABORT:
        // The process should exit now
        // Terminate the process so we don't go through all that
        // .dll cleanup code. This'll avoid mfc dumping heap
        // allocation info to the debugger, making termination
        // faster.

        TerminateProcess(GetCurrentProcess(), 0);
        return;

    case IDRETRY:
        // This'll break into the debugger or cause the just
        // in time debugger to load. If neither are present, the app
        // will terminate.

        OutputDebugString(szT);

        _asm {
            int 3;
        }

        // Just continue and hope things get better

        return;

	case IDIGNORE:
        // Output assertion string. Can also be used to ignore
		// asserts.

        OutputDebugString(szT);
        return;
    }
}

void __cdecl DoAssertRip(int fNoAssert, char *psz, ...)
{
    if (fNoAssert)
        return;

    va_list va;
    va_start(va, psz);
    DoRip("Assertion failed!", psz, va);
    va_end(va);
}

void __cdecl DoAssertRip(int fNoAssert)
{
    if (fNoAssert)
		return;

    DoRip("Assertion failed!", "", NULL);
}

void __cdecl DoAssertRip(char *psz, ...)
{
    va_list va;
    va_start(va, psz);
    DoRip("Assert!", psz, va);
    va_end(va);
}

void __cdecl DoAssertRip()
{
	DoAssertRip("Unknown error");
}

#endif // _DEBUG

