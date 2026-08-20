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
// Property.h
//
// For setting / getting / saving / loading string and integer properties
// persisted in textual format
/////////////////////////////////////////////////////////////////////////////

#if !defined(__PROPERTY_H__)
#define __PROPERTY_H__

#include "StdIo.h"

typedef unsigned long ulong;

// OosClose class, for closing files when going out of scope

class OosClose
{
public:
	inline OosClose(FILE *pf)
	{
		m_pf = pf;
	}
	inline ~OosClose()
	{
		fclose(m_pf);
	}

private:
    FILE *m_pf;
};

// Use line number for uniqueness in naming, since this can be used
// multiple times within one scope.

#define OosClose(pf) OosClose osc##__LINE__((FILE *)##pf)

// Position class, used for enumeration

const ulong kPosFirst = (ulong)-1;

class Position // pos
{
public:
    Position()
	{
        m_pvNext = (void *)kPosFirst;
		m_ulUser = kPosFirst;
    }
    void Reset()
	{
        m_pvNext = (void *)kPosFirst;
		m_ulUser = kPosFirst;
    }

    void *m_pvNext;
    ulong m_ulUser;
};

class PropertySection;
class Property;

class Property // prop
{
public:
	Property();
	~Property();

	bool Init(const char *pszKey, const char *pszValue);
	bool SetValue(const char *pszValue);

private:
	Property *m_ppropNext;
	char *m_pszKey;
	char *m_pszValue;

	friend PropertySection;
};

class PropertySection // sec
{
public:
	PropertySection();
	~PropertySection();
	
	bool Init(const char *pszName);
	bool Load(const char *pszFilename);
	bool Save(const char *pszFilename);

	PropertySection *FindChildSection(const char *pszName);
	PropertySection *GetNextChildSection(Position *ppos, char *pszName, ulong cb);
	PropertySection *CreateChildSection(const char *pszName);
	char *GetString(const char *pszKey, char *pszDefault);
	long GetLong(const char *pszKey, long lDefault = 0);
	float GetFloat(const char *pszKey, float nfDefault = 0.0f);
	bool SetString(const char *pszKey, const char *pszValue);
	bool SetLong(const char *pszKey, long l);
	bool SetFloat(const char *pszKey, float nf);

private:
	bool Load2(FILE *pf);
	bool Save2(FILE *pf, int cLevelIndent);
	
	PropertySection *m_psecChild;
	PropertySection *m_psecNext;
	Property *m_ppropFirst;
	char *m_pszName;
};

PropertySection *CreatePropertySection(const char *pszFilename = NULL);

#endif // !defined(__PROPERTY_H__)
