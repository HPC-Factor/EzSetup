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

#ifndef __RIP_H__
#define __RIP_H__

#ifdef _DEBUG

// These are macroized solely so they can be redefined. This is useful
// if the below macros are going to be used in helper functions, where you
// want the file and line of the caller and not the helper function.

#define __FILE __FILE__
#define __LINE __LINE__

//
// The below macros constitute system support for asserts, warnings,
// bad param reporting, and rips.//
// The macros are:
//
//   Assert(f, ...)
//      Standard assertion macro.  If present, the second parameter is a
//      sprintf format string.

// These globals need to be defined for rip to work.

extern char *gpszRipFile;
extern int giRipLine;

void __cdecl DoAssertRip(int fAssert, char *psz, ...);
void __cdecl DoAssertRip(int fAssert);
void __cdecl DoAssertRip(char *psz, ...);
void __cdecl DoAssertRip();

#define Assert   gpszRipFile = __FILE, giRipLine = __LINE, ::DoAssertRip

#else // _DEBUG

// This hack allows us to create varargs macros that compile to nothing
// on release.

inline void __cdecl DoConditionalRip(int, ...) { }
inline void __cdecl DoConditionalRip(char *psz, ...) { }
inline void __cdecl DoConditionalRip() { }

#define Assert             1 ? (void)0 : ::DoConditionalRip

#endif // _DEBUG

#endif // __RIP_H__
