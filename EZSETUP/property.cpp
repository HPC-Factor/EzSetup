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
// Property.cpp
//
// Code for reading / writing named properties textually & hierarchically
/////////////////////////////////////////////////////////////////////////////

#include "Windows.h"
#include "Property.h"
#include "Rip.h"

// File format is either flat .ini file [] format, or hierarchical begin / end format:
//
// [SectionName]
// KeyName = Value
//
// -or-
//
// Begin SectionName
//    KeyName = Value
//    Begin SectionName
//        KeyName = Value
//        KeyName = Value
//    End
// End
//
// Values are strings, which can be retrieved as ints if numerical.
//
// Which format is controlled by this define:

//#define BEGINEND

bool AllocString(char **ppszDst, const char *pszSrc)
{
	delete *ppszDst;
	int cch = strlen(pszSrc);
	*ppszDst = new char[cch + 1];
	if (*ppszDst != NULL) {
		strcpy(*ppszDst, pszSrc);
		return TRUE;
	}
	return FALSE;
}

Property::Property()
{
	m_ppropNext = NULL;
	m_pszKey = NULL;
	m_pszValue = NULL;
}

Property::~Property()
{
	delete m_pszKey;
	delete m_pszValue;
}

bool Property::Init(const char *pszKey, const char *pszValue)
{
	if (!AllocString(&m_pszKey, pszKey))
		return FALSE;
	return SetValue(pszValue);
}

bool Property::SetValue(const char *pszValue)
{
	return AllocString(&m_pszValue, pszValue);
}

PropertySection::PropertySection()
{
	m_psecChild = NULL;
	m_psecNext = NULL;
	m_ppropFirst = NULL;
	m_pszName = NULL;
}

PropertySection::~PropertySection()
{
	PropertySection *psec = m_psecChild;
	while (psec != NULL) {
		PropertySection *psecNext = psec->m_psecNext;
		delete psec;
		psec = psecNext;
	}

	Property *pprop;
	while ((pprop = m_ppropFirst) != NULL) {
		m_ppropFirst = m_ppropFirst->m_ppropNext;
		delete pprop;
	}
	delete m_pszName;
}

bool PropertySection::Init(const char *pszName)
{
	return AllocString(&m_pszName, pszName);
}

PropertySection *PropertySection::FindChildSection(const char *pszName)
{
	// NOTE: Sorted linear search. If necessary this can be
	// made much faster with a tree approach.

	PropertySection *psec;
	for (psec = m_psecChild; psec != NULL; psec = psec->m_psecNext) {
		if (_stricmp(pszName, psec->m_pszName) == 0)
			return psec;
	}
	return NULL;
}

PropertySection *PropertySection::GetNextChildSection(Position *ppos,
		char *pszName, ulong cb)
{
	if (ppos->m_pvNext == (void *)kPosFirst) {
		ppos->m_pvNext = m_psecChild;
	} else {
		ppos->m_pvNext = ((PropertySection *)(ppos->m_pvNext))->m_psecNext;
	}

	if (ppos->m_pvNext != NULL) {
		strncpy(pszName, ((PropertySection *)(ppos->m_pvNext))->m_pszName, cb);
		pszName[cb - 1] = 0;
	}

	return (PropertySection *)ppos->m_pvNext;
}

PropertySection *PropertySection::CreateChildSection(const char *pszName)
{
	// Insert in order

	PropertySection **ppsec;
	for (ppsec = &m_psecChild; *ppsec != NULL; ppsec = &(*ppsec)->m_psecNext) {
		// If our key is less than the current key, we've
		// found the insertion point.

		int n = strcmp(pszName, (*ppsec)->m_pszName);
		if (n < 0)
			break;
	}

	// We're either at the end of the properties or we've stopped in
	// sorted order

	PropertySection *psec = new PropertySection;
	if (!psec->Init(pszName)) {
		delete psec;
		return NULL;
	}
	psec->m_psecNext = *ppsec;
	*ppsec = psec;

	return psec;
}

char *PropertySection::GetString(const char *pszKey, char *pszDefault)
{
	Property *pprop;
	for (pprop = m_ppropFirst; pprop != NULL; pprop = pprop->m_ppropNext) {
		if (_stricmp(pszKey, pprop->m_pszKey) == 0)
			return pprop->m_pszValue;
	}
	return pszDefault;
}

long PropertySection::GetLong(const char *pszKey, long lDefault)
{
	// NOTE: Everything is stored as strings; we'll probably
	// hit string to long conversion once for most things, so it
	// isn't a performance problem, however it means more memory
	// is consumed.

	char *psz = GetString(pszKey, NULL);
	if (psz == NULL)
		return lDefault;
	return atol(psz);
}

float PropertySection::GetFloat(const char *pszKey, float nfDefault)
{
	// NOTE: Everything is stored as strings; we'll probably
	// hit string to long conversion once for most things, so it
	// isn't a performance problem, however it means more memory
	// is consumed.

	char *psz = GetString(pszKey, NULL);
	if (psz == NULL)
		return nfDefault;
	return (float)atof(psz);
}

bool PropertySection::SetString(const char *pszKey, const char *pszValue)
{
	// Insert in order

	Property **ppprop;
	for (ppprop = &m_ppropFirst; *ppprop != NULL; ppprop =
				&(*ppprop)->m_ppropNext) {
		// If the keys are the same, reset the value.
		// If our key is less than the current key, we've
		// found the insertion point.

		int n = strcmp(pszKey, (*ppprop)->m_pszKey);
		if (n == 0)
			return (*ppprop)->SetValue(pszValue);
		if (n < 0)
			break;
	}

	// We're either at the end of the properties or we've stopped in
	// sorted order

	Property *pprop = new Property;
	if (!pprop->Init(pszKey, pszValue)) {
		delete pprop;
		return FALSE;
	}
	pprop->m_ppropNext = *ppprop;
	*ppprop = pprop;

	return TRUE;
}

bool PropertySection::SetLong(const char *pszKey, long l)
{
	char szT[32];
	return SetString(pszKey, _ltoa(l, szT, 10));
}

bool PropertySection::SetFloat(const char *pszKey, float nf)
{
	char szT[32];
	return SetString(pszKey, _gcvt((double)nf, 10, szT));
}

bool PropertySection::Load(const char *pszFilename)
{
	// Assumption that this has nothing in it right now.

	Assert(m_psecChild == NULL);
	Assert(m_psecNext == NULL);
	Assert(m_ppropFirst == NULL);

	FILE *pf = fopen(pszFilename, "rt");
	if (pf == NULL || pf == (FILE *)-1) {
		Assert("Couldn't open %s", pszFilename);
		return FALSE;
	}
	OosClose(pf);

	// The first property set to load doesn't have
	// a begin / end, it is implicit (bof means begin,
	// eof means end)
	
	return Load2(pf);
}

#ifdef BEGINEND
// Heirarchical Begin / End pairs

bool PropertySection::Load2(FILE *pf)
{
	char szKey[128];
	char szValue[512];

	while (TRUE) {
		int n = fscanf(pf, "\t%s\t", szKey);

		// If we read nothing, it may be an empty line.
		// If it is eof, it's an implicit end

		if (n != 1) {
			if (feof(pf))
				return TRUE;
			continue;
		}

		// If end, we're done for this section

		if (strcmp(szKey, "End") == 0)
			return TRUE;

		// If begin, get the name and create new section

		if (strcmp(szKey, "Begin") == 0) {
			n = fscanf(pf, "%s\n", szValue);
			if (n != 1)
				return FALSE;
			PropertySection *psec = CreateChildSection(szValue);
			if (psec == NULL)
				return FALSE;
			if (!psec->Load2(pf))
				return FALSE;
			continue;
		}

		// See if it is a prop/value pair

		n = fscanf(pf, "=\t%[^\n]", szValue);
		if (n != 1)
			return FALSE;
		SetString(szKey, szValue);
	}
}
#else
// Flat .ini file style [Name] sections

bool PropertySection::Load2(FILE *pf)
{
	char sz[512];
	char szSection[128];
	char szKey[128];
	char szValue[512];

	while (true) {
		if (fgets(sz, sizeof(sz), pf) == NULL)
			return feof(pf) != 0;

		while (true) {
			// If we read nothing that matches a section
			// header, assume it is an empty line.

			int n = sscanf(sz, "\t[%[^]]]\t\n", szSection);
			if (n != 1)
				break;

			PropertySection *psec = CreateChildSection(szSection);
			if (psec == NULL)
				return false;

			// Now load in prop / value pairs

			while (true) {
				// See if it is a prop/value pair, if not it may be
				// another section beginning

				if (fgets(sz, sizeof(sz), pf) == NULL)
					return feof(pf) != 0;

				n = sscanf(sz, "\t%s\t=\t%[^\n]", szKey, szValue);
				if (n != 2)
					break;
				psec->SetString(szKey, szValue);
			}
		}
	}
}
#endif

bool PropertySection::Save(const char *pszFilename)
{
	FILE *pf = fopen(pszFilename, "wt");
	if (pf == NULL || pf == (FILE *)-1) {
		Assert("Couldn't open %s", pszFilename);
		return FALSE;
	}
	OosClose(pf);

	// The first property set to save doesn't save it's
	// name or indent its contents!

	return Save2(pf, 0);
}

bool PropertySection::Save2(FILE *pf, int cLevelIndent)
{
	// Calculate a string for the indentation level

	char szIndent[80];
	for (int i = 0; i < cLevelIndent && i < sizeof(szIndent) - 1; i++)
		szIndent[i] = '\t';
	szIndent[i] = 0;

	// The header for this property set has already been saved
	// out. Print out the contents here, properties first

	Property *pprop;
	for (pprop = m_ppropFirst; pprop != NULL; pprop = pprop->m_ppropNext) {
		fprintf(pf, "%s%s = %s\n", szIndent, pprop->m_pszKey,
				pprop->m_pszValue);
	}

	// Print out child property sets

	PropertySection *psec;
	for (psec = m_psecChild; psec != NULL; psec = psec->m_psecNext) {
		fprintf(pf, "%sBegin %s\n", szIndent, psec->m_pszName);
		psec->Save2(pf, cLevelIndent + 1);
		fprintf(pf, "%sEnd\n", szIndent);
		if (cLevelIndent == 0)
			fprintf(pf, "\n");
	}

	return TRUE;
}

PropertySection *CreatePropertySection(const char *pszFilename)
{
	// Create a new property set

	PropertySection *psec = new PropertySection;
	if (!psec->Init("TopSection")) {
		delete psec;
		return NULL;
	}

	// Initialize it from this file

	if (pszFilename != NULL) {
		if (!psec->Load(pszFilename)) {
			delete psec;
			return NULL;
		}
	}

	return psec;
}


