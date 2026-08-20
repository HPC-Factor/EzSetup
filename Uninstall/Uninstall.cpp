// Uninstall.cpp : Defines the entry point for the application.
//

// Module name: DeleteMe.cpp
// Written by: Jeffrey Richter
// Description: Allows an executable file to delete itself

#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

// The name of the temporary batch file
#define DELUNSETUPBAT     __TEXT("\\DelUS.bat")

#define EVT_NAME  _T("ExeDeleteEvent")

void WINAPI DeleteExecutableBF(void) {
   HANDLE hfile;
   STARTUPINFO si;
   PROCESS_INFORMATION pi;

   // Create a batch file that continuously attempts to delete our executable
   // file.  When the executable no longer exists, remove its containing
   // subdirectory, and then delete the batch file too.
   hfile = CreateFile(DELUNSETUPBAT, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
   if (hfile != INVALID_HANDLE_VALUE) {

      TCHAR szBatFile[1000];
      TCHAR szUnsetupPathname[_MAX_PATH];
      TCHAR szUnsetupPath[_MAX_PATH];
      DWORD dwNumberOfBytesWritten;

      // Get the full pathname of our executable file.
      GetModuleFileName(NULL, szUnsetupPathname, _MAX_PATH);

      // Get the path of the executable file (without the filename)
      lstrcpy(szUnsetupPath, szUnsetupPathname);
      *_tcsrchr(szUnsetupPath, __TEXT('\\')) = 0;     // Chop off the name


      // Construct the lines for the batch file.
      wsprintf(szBatFile,
         __TEXT(":Repeat\r\n")
         __TEXT("del \"%s\"\r\n")
         __TEXT("if exist \"%s\" goto Repeat\r\n")
         __TEXT("del \"%s\\*.*\" /F /S /Q\r\n")
         __TEXT("rmdir \"%s\"\r\n")
         __TEXT("del \"%s\"\r\n"), 
         szUnsetupPathname, szUnsetupPathname, szUnsetupPath, szUnsetupPath, DELUNSETUPBAT);

      // Write the batch file and close it.
      WriteFile(hfile, szBatFile, lstrlen(szBatFile) * sizeof(TCHAR),
         &dwNumberOfBytesWritten, NULL);
      CloseHandle(hfile);

      // Get ready to spawn the batch file we just created.
      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);

      // We want its console window to be invisible to the user.
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE;

      // Spawn the batch file with low-priority and suspended.
      if (CreateProcess(NULL, DELUNSETUPBAT, NULL, NULL, FALSE,
         CREATE_SUSPENDED | IDLE_PRIORITY_CLASS, NULL, __TEXT("\\"), &si, &pi)) {

         // Lower the batch file's priority even more.
         SetThreadPriority(pi.hThread, THREAD_PRIORITY_IDLE);

         // Raise our priority so that we terminate as quickly as possible.
         SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
         SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

         // Allow the batch file to run and clean-up our handles.
         CloseHandle(pi.hProcess);
         ResumeThread(pi.hThread);
         // We want to terminate right away now so that we can be deleted
         CloseHandle(pi.hThread);
      }
   }
}

BOOL DeleteSubkey(HKEY hkey, LPCTSTR pcszSubkey)
{
	if(!pcszSubkey)
		return FALSE;
	else
	{
		// Recursively delete any subkeys for the target subkey
		HKEY	hkeySubkey;
		char	strSubkey[4096];

		DWORD dwRC = RegOpenKeyEx(hkey, pcszSubkey, 0, KEY_ALL_ACCESS, &hkeySubkey);

		if(dwRC != ERROR_SUCCESS)
		{
			return FALSE;
		}

		DWORD	dwNameSize = MAX_PATH;

		while(RegEnumKeyEx(hkeySubkey, 0, strSubkey, &dwNameSize, 0, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			if(! DeleteSubkey(hkeySubkey, strSubkey))
			{
				RegCloseKey(hkeySubkey);
				return FALSE;
			}

			dwNameSize = MAX_PATH;
		}

		RegCloseKey(hkeySubkey);
	}
	
	return (RegDeleteKey(hkey, pcszSubkey) == ERROR_SUCCESS);
}

void DeleteUnregisterInformation(LPCTSTR szProjectName)
{
	HKEY hUninstall;
	LONG lr;

	lr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_QUERY_VALUE|KEY_CREATE_SUB_KEY, &hUninstall);
	if (lr != ERROR_SUCCESS) {
		return;
	}

	::DeleteSubkey(hUninstall, szProjectName);

	RegCloseKey(hUninstall);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR pszCmdLine, int nCmdShow)
{
	//Get product name
	char strFullPath[MAX_PATH+1];
	char strDrive[_MAX_DRIVE];
	char strDir[_MAX_DIR];
	char strFname[_MAX_FNAME];
	char strExt[_MAX_EXT];
	char *strProduct;

	::GetModuleFileName(NULL, strFullPath, MAX_PATH);
	_splitpath(strFullPath, strDrive, strDir, strFname, strExt);

	int nFolderLength = strlen(strDir);
	if (strDir[nFolderLength-1]=='\\') {
		strDir[nFolderLength-1] = 0;
		nFolderLength--;
	}
	int i;
	for (i=nFolderLength-1; i>0; i--) {
		if (strDir[i]=='\\') break;
	}
	strProduct = strDir+i+1;

	DeleteUnregisterInformation(strProduct);
	DeleteExecutableBF();
	return 0;
}