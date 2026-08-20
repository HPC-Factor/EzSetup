// EzSetup - an CE app install maker
// Copyright (C) 2002 Spb Software House
// info@softspb.com
// http://www.softspb.com
//
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

#include <windows.h>
#include <stdio.h>
#include "property.h"
#include "resource.h"

bool FilePresent(char *pszFn)
{
	HANDLE h = CreateFile(pszFn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	CloseHandle(h);
	return true;
}

DWORD FileSize(char *pszFn)
{
	HANDLE h = CreateFile(pszFn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE)
		return 0;
	DWORD dw = GetFileSize(h, NULL);
	CloseHandle(h);
	return dw;
}

BYTE *GetResourcePtr(int idr, int *pcb)
{
	HRSRC hr = FindResource(NULL, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(99));
	if (hr == NULL)
		return NULL;
	*pcb = SizeofResource(NULL, hr);
	HGLOBAL h = LoadResource(NULL, hr);
	return (BYTE *)LockResource(h);
}

bool WriteToFile(BYTE *pb, int cb, char *psz)
{
	// Create the file and write these bytes

	HANDLE h = CreateFile(psz, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	int cbWritten = 0;
	if (!WriteFile(h, pb, cb, (DWORD *)&cbWritten, NULL) || cb != cbWritten)
		return false;
	CloseHandle(h);
	return true;
}

void GetTempFn(char *pszWorkingDir, char *pszFile)
{
	GetTempFileName(pszWorkingDir, "ezs", 0, pszFile);
}

#define kidrEula 5
#define kidrReadme 4
#define kidrIniFile 1
#define kidrFirstCab 2
#define kidrDirectory 2
#define kidtCEAPPMGRFILES 100
#define kidtCEAPPMGRFILENAMES 101
#define kidtTEXTFILES 102
#define kidtMISCSTRINGS 103

byte *MapFile(char *psz, int *pcb, HANDLE *phMap)
{
	*pcb = FileSize(psz);
	HANDLE hFile = CreateFile(psz, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("Error reading in file %s!", psz);
		return NULL;
	}
	*phMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	CloseHandle(hFile);
	if (*phMap == NULL) {
MapError:		
		printf("Error mapping view of file %s!", psz);
		return NULL;
	}
	byte *pb = (BYTE *)MapViewOfFile(*phMap, FILE_MAP_READ, 0, 0, 0);
	if (pb == NULL) {
		CloseHandle(*phMap);
		goto MapError;
	}
	return pb;
}

bool WriteFileToResource(char *pszFn, HANDLE h, int idt, int idr)
{
	int cb;
	HANDLE hMap;
	byte *pb = MapFile(pszFn, &cb, &hMap);
	if (pb == NULL)
		return false;
	if (!UpdateResource(h, MAKEINTRESOURCE(idt), MAKEINTRESOURCE(idr), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), pb, cb)) {
		printf("Error updating resource of temp file!", pszFn);
		UnmapViewOfFile(pb);
		CloseHandle(hMap);
		return false;
	}
	UnmapViewOfFile(pb);
	CloseHandle(hMap);
	return true;
}

bool WriteStringToResource(char *psz, HANDLE h, int idt, int idr)
{
	if (!UpdateResource(h, MAKEINTRESOURCE(idt), MAKEINTRESOURCE(idr), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), psz, strlen(psz) + 1)) {
		printf("Error updating resource of temp file!");
		return false;
	}
	return true;
}

void GetFilenameOnly(char *pszFnIn, char *pszFnOut)
{
	char szFullPath[MAX_PATH];
	_fullpath(szFullPath, pszFnIn, sizeof(szFullPath));
	char szDrive[_MAX_DRIVE];
	char szDir[MAX_PATH];
	char szExt[MAX_PATH];
	_splitpath(szFullPath, szDrive, szDir, pszFnOut, szExt);
	strcat(pszFnOut, szExt);
}

// Text files aren't zero extended, so we need to do this

bool ZeroExtendFile(char *pszDir, char *pszFnIn, char *pszFnOut)
{
	GetTempFn(pszDir, pszFnOut);
	int cb;
	HANDLE hMap;
	byte *pb = MapFile(pszFnIn, &cb, &hMap);
	if (pb == NULL) {
		printf("Error reading file %s!\n", pszFnIn);
		return false;
	}

	HANDLE h = CreateFile(pszFnOut, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	int cbWritten = 0;
	if (!WriteFile(h, pb, cb, (DWORD *)&cbWritten, NULL) || cb != cbWritten) {
		UnmapViewOfFile(pb);
		CloseHandle(hMap);
WriteError:
		printf("Error writing to temporary file %s!\n", pszFnOut);
		CloseHandle(h);
		return false;
	}
	UnmapViewOfFile(pb);
	CloseHandle(hMap);
	byte b = 0;
	if (!WriteFile(h, &b, 1, (DWORD *)&cbWritten, NULL) || cbWritten != 1)
		goto WriteError;
	CloseHandle(h);
	return true;
}

bool WriteNewCESetup(UINT idr, char *pszDir, char *pszComponent, char *pszFnIni, char *pszFnReadme, char *pszFnEula, int cCabs, char aszFnCabs[20][MAX_PATH], char *pszFnExeT)
{
	// Write uninstallation to a temportary file

	int uninstallCb;
	byte *pUninstallB = GetResourcePtr(kidrUninstall, &uninstallCb);
	char pszUninstallT[MAX_PATH+1];
	GetTempFn(pszDir, pszUninstallT);

	// Write to file

	if (!WriteToFile(pUninstallB, uninstallCb, pszUninstallT)) {
		printf("Error writing uninstall to temporary file %s!\n", pszUninstallT);
		return false;
	}

	// First write out the empty cesetup
	int cb;
	byte *pb = GetResourcePtr(idr, &cb);
	*pszFnExeT = 0;
	GetTempFn(pszDir, pszFnExeT);

	// Write to file

	if (!WriteToFile(pb, cb, pszFnExeT)) {
		printf("Error writing to temporary file %s!\n", pszFnExeT);
		DeleteFile(pszUninstallT);
		return false;
	}

	// Write in the new resources

	HANDLE h = BeginUpdateResource(pszFnExeT, FALSE);
	if (h == NULL) {
		printf("Error opening temporary file %s!\n", pszFnExeT);
ExeCleanup:
		DeleteFile(pszFnExeT);
		DeleteFile(pszUninstallT);
		return false;
	}

	// Write the .ini file

	if (!WriteFileToResource(pszFnIni, h, kidtCEAPPMGRFILES, kidrIniFile)) {
		EndUpdateResource(h, TRUE);
		goto ExeCleanup;
	}

	// Write the .ini filename	

	char szFn[MAX_PATH];
	GetFilenameOnly(pszFnIni, szFn);
	if (!WriteStringToResource(szFn, h, kidtCEAPPMGRFILENAMES, kidrIniFile)) {
		EndUpdateResource(h, TRUE);
		goto ExeCleanup;
	}

	// Write uninstallation
       	if (!WriteFileToResource(pszUninstallT, h, kidtCEAPPMGRFILES, kidrFirstCab)) {
       		EndUpdateResource(h, TRUE);
       		goto ExeCleanup;
       	}

       	if (!WriteStringToResource("Uninstall.exe", h, kidtCEAPPMGRFILENAMES, kidrFirstCab)) {
       		EndUpdateResource(h, TRUE);
       		goto ExeCleanup;
       	}

	// Write .cabs

	for (int i = 0; i < cCabs; i++) {
		if (!WriteFileToResource(&aszFnCabs[i][0], h, kidtCEAPPMGRFILES, kidrFirstCab + i + 1)) {
			EndUpdateResource(h, TRUE);
			goto ExeCleanup;
		}

		GetFilenameOnly(&aszFnCabs[i][0], szFn);
		if (!WriteStringToResource(szFn, h, kidtCEAPPMGRFILENAMES, kidrFirstCab + i + 1)) {
			EndUpdateResource(h, TRUE);
			goto ExeCleanup;
		}
	}

	// Write readme

	ZeroExtendFile(pszDir, pszFnReadme, szFn);
	if (!WriteFileToResource(szFn, h, kidtTEXTFILES, kidrReadme)) {
		EndUpdateResource(h, TRUE);
		DeleteFile(szFn);
		goto ExeCleanup;
	}
	DeleteFile(szFn);

	// Write eula

	ZeroExtendFile(pszDir, pszFnEula, szFn);
	if (!WriteFileToResource(szFn, h, kidtTEXTFILES, kidrEula)) {
		EndUpdateResource(h, TRUE);
		DeleteFile(szFn);
		goto ExeCleanup;
	}
	DeleteFile(szFn);

	// Write directory name to install (which is component name)

	if (!WriteStringToResource(pszComponent, h, kidtMISCSTRINGS, kidrDirectory)) {
		EndUpdateResource(h, TRUE);
		goto ExeCleanup;
	}

	// We're done

	EndUpdateResource(h, FALSE);
	DeleteFile(pszUninstallT);
	return true;
}

bool CompressExe(char *pszDir, char *pszFnExeT)
{
	// Write cexe.exe resource to temp file
	
	int cb;
	byte *pb = GetResourcePtr(kidrCExe, &cb);
	char szCEXE[MAX_PATH];
	szCEXE[0] = 0;
	GetTempFn(pszDir, szCEXE);
	if (!WriteToFile(pb, cb, szCEXE)) {
		printf("Error writing to temporary file %s!\n", szCEXE);
		return false;
	}

	// Execute cexe with pszFnExeT as parameter, wait on result

	char szCmdLine[MAX_PATH];
	lstrcpy(szCmdLine, "\"");
	lstrcat(szCmdLine, szCEXE);
	lstrcat(szCmdLine, "\" ");
	lstrcat(szCmdLine, "\"");
	lstrcat(szCmdLine, pszFnExeT);
	lstrcat(szCmdLine, "\"");

	STARTUPINFO snfo;
	GetStartupInfo(&snfo);
	PROCESS_INFORMATION pi;
	if (!CreateProcess(NULL, szCmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &snfo, &pi)) {
		DeleteFile(szCEXE);
Error:
		printf(".exe compression failed!\n");
		return false;
	}
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD dwExit;
	GetExitCodeProcess(pi.hProcess, &dwExit);
	CloseHandle(pi.hProcess);

	// Delete temp file CEXE

	DeleteFile(szCEXE);

	if (dwExit != 0)
		goto Error;
	return true;
}

void Usage()
{
	printf("\n");
	printf("EzSetup v2.1, January 2003, Freeware\n");
	printf("\n");
	printf("Usage:\n");
	printf("ezsetup <-l language> <-i inifilename> <-r readme.txt> <-e eula.txt> <-o outputexe>\n");
	printf("\n");
	printf("Creates a compressed, self-contained and self-extracting Win32 gui install\n");
	printf("application that when run on your desktop PC will install a Pocket PC application\n");
	printf("to a Pocket PC device. To operate, ezsetup simply needs your .ini\n");
	printf("and .cab files, a readme.txt file and a eula.txt file. (For more info on\n");
	printf(".ini and .cab files, see your Pocket PC SDK documentation).\n");
	printf("\n");
	printf("<-l language>\n");
	printf("    This is specifies the language text of the install program. Valid argument\n");
	printf("    are 'english', 'german', 'french', 'italian', 'swedish', 'portuguese' and 'spanish'.\n");
	printf("\n");
	printf("<-i inifilename>\n");
	printf("    This parameter specifies the .ini file used as part of CE App Mgr setup.\n");
	printf("    The .cab files specified in this .ini file are expected to be in the same\n");
	printf("    directory as the .ini file, and are read in by ezsetup.\n");
	printf("\n");
	printf("<-r readme.txt>\n");
	printf("    Specify a readme.txt file that will appear as the first dialog in the\n");
	printf("    gui setup program.\n");
	printf("\n");
	printf("<-e eula.txt>\n");
	printf("    Specify an end-user license agreement that will appear as the second\n");
	printf("    dialog in the gui setup program.\n");
	printf("\n");
	printf("<-o outputexe>\n");
	printf("    This parameter specifies the output name of the resulting compressed\n");
	printf("    auto-extracting setup executable.\n");
	printf("\n");
	printf("Example:\n");
	printf("ezsetup -l english -i chess.ini -r readme.txt -e eula.txt -o ChessSetup.exe\n");
	printf("\n");
	printf("Note: EzSetup runs on WindowsNT/2000/XP or later versions only. The executables\n");
    printf("it produces will run on any Win32 platform.\n");
	printf("\n");
	printf("Spb Software House, http://www.softspb.com, info@softspb.com\n");
	printf("Tinyware, Inc, http://www.eskimo.com/~scottlu, scottlu@eskimo.com\n");
}

int main(int argc, char *argv[])
{
	// Read in command line arguments

	char szLanguage[256];
	char szFnEzSetup[MAX_PATH];
	char szFnIni[MAX_PATH];
	char szFnReadme[MAX_PATH];
	char szFnEula[MAX_PATH];
	char szFnExe[MAX_PATH];

	char *psz = GetCommandLine();
	if (sscanf(GetCommandLine(), "%s -l %s -i %s -r %s -e %s -o %s", szFnEzSetup, szLanguage, szFnIni, szFnReadme, szFnEula, szFnExe) != 6) {
		Usage();
		return -1;
	}

	// Parse for appropriate language

	UINT idrSetup = (UINT)-1;
	if (stricmp(szLanguage, "english") == 0) {
		idrSetup = kidrSetupEnglish;
	} else if (stricmp(szLanguage, "french") == 0) {
		idrSetup = kidrSetupFrench;
	} else if (stricmp(szLanguage, "spanish") == 0) {
		idrSetup = kidrSetupSpanish;
	} else if (stricmp(szLanguage, "italian") == 0) {
		idrSetup = kidrSetupItalian;
	} else if (stricmp(szLanguage, "portuguese") == 0) {
		idrSetup = kidrSetupPortuguese;
	} else if (stricmp(szLanguage, "swedish") == 0) {
		idrSetup = kidrSetupSwedish;
	} else if (stricmp(szLanguage, "german") == 0) {
		idrSetup = kidrSetupGerman;
	}
	if (idrSetup == (UINT)-1) {
		printf("Valid language not specified.\n\n");
		return -1;
	}

	// Read in the .ini file

	PropertySection *pprop = CreatePropertySection(szFnIni);
	if (pprop == NULL) {
IniError:
		printf("Error reading .ini file: %s\n\n", szFnIni);
		return -1;
	}

	// Get the name of the component

	PropertySection *ppropAppMgr = pprop->FindChildSection("CEAppManager");
	if (ppropAppMgr == NULL) {
		printf("Could not find [CEAppManager] section in .ini file!\n");
		goto IniError;
	}
	char *pszComponent = ppropAppMgr->GetString("Component", NULL);
	if (pszComponent == NULL) {
		printf("Could not find Component key in [CEAppManager] section in .ini file!\n");
		goto IniError;
	}

	// Now grab the .cab file names from the component section

	PropertySection *ppropComponent = pprop->FindChildSection(pszComponent);
	if (ppropComponent == NULL) {
		printf("Could not find component [%s] section in .ini file!\n", pszComponent);
		goto IniError;
	}
	char *pszCabs = ppropComponent->GetString("CabFiles", NULL);
	if (pszCabs == NULL) {
		printf("Could not find CabFiles key in [%s] section!\n", pszComponent);
		goto IniError;
	}

	// Good so far. Now break out pszCabs into a list of filenames

	char aszFnCabs[20][MAX_PATH];
	int cCabs = sscanf(pszCabs, "\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n],\t%[^,\n]",
			&aszFnCabs[0], &aszFnCabs[1], &aszFnCabs[2], &aszFnCabs[3], &aszFnCabs[4], &aszFnCabs[5],
			&aszFnCabs[6], &aszFnCabs[7], &aszFnCabs[8], &aszFnCabs[9], &aszFnCabs[10], &aszFnCabs[11],
			&aszFnCabs[12], &aszFnCabs[13], &aszFnCabs[14], &aszFnCabs[15], &aszFnCabs[16], &aszFnCabs[17],
			&aszFnCabs[18], &aszFnCabs[19]);
	if (cCabs == 0) {
		printf("Error parsing CabFiles value in [%s] section!\n", pszComponent);
		goto IniError;
	}

	// Check to make sure all files are present

	if (!FilePresent(szFnReadme)) {
		printf("Could not find readme text file %s!\n", szFnReadme);
		return -1;
	}
	if (!FilePresent(szFnEula)) {
		printf("Could not find eula text file %s!\n", szFnEula);
		return -1;
	}
	for (int i = 0; i < cCabs; i++) {
		if (!FilePresent(&aszFnCabs[i][0])) {
			printf("Could not find .cab file %s!\n", &aszFnCabs[i][0]);
			return -1;
		}
	}

	// Now print full paths of files read in

	printf("Reading files...\n");
	char szT[MAX_PATH];
	_fullpath(szT, szFnIni, sizeof(szT));
	printf("%s\n", szT);
	_fullpath(szT, szFnReadme, sizeof(szT));
	printf("%s\n", szT);
	_fullpath(szT, szFnEula, sizeof(szT));
	printf("%s\n", szT);
	for (i = 0; i < cCabs; i++) {
		_fullpath(szT, &aszFnCabs[i][0], sizeof(szT));
		printf("%s\n", szT);
	}
	printf("\n");

	// Ready to get to work. Figure out what directory the result
	// is being written to.

	_fullpath(szT, szFnExe, sizeof(szT));
	char szDrive[_MAX_DRIVE];
	char szDir[MAX_PATH];
	char szName[MAX_PATH];
	char szExt[MAX_PATH];
	_splitpath(szT, szDrive, szDir, szName, szExt);

	char szFnExeT[MAX_PATH];
	if (!WriteNewCESetup(idrSetup, szDir, pszComponent, szFnIni, szFnReadme, szFnEula, cCabs, aszFnCabs, szFnExeT))
		return -1;

	// Now compress this new app

	printf("Compressing file...\n");
	if (!CompressExe(szDir, szFnExeT)) {
		DeleteFile(szFnExeT);
		return -1;
	}

	// We're just about done! Now copy to new filename - done this way so
	// in case we exit inappropriately, the old filename (if it exists)
	// doesn't get written to.

	if (!CopyFile(szFnExeT, szFnExe, FALSE)) {
		printf("Error copying %s to %s!\n", szFnExeT, szFnExe);
		DeleteFile(szFnExeT);
		return -1;
	}
	DeleteFile(szFnExeT);

	// Now print status and exit

	printf("%s successfully written.\n", szFnExe);
	printf("%d bytes.\n", FileSize(szFnExe));
	printf("\n");

	// Delete parent property section

	delete pprop;
	
	return 0;
}
