// Setup - an win32 gui CE app setup program, meant to be used in conjunction with EzSetup.
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
#include "resource.h"
#include "Wizard.h"

HINSTANCE ghInst;
HWND ghTitle;
HWND ghSubTitle;
RECT grtWhiteBanner;

class ResourceString
{
public:
	ResourceString(UINT idr);
	char m_sz[256];
};

HWND CreateStatic(LPCTSTR strText, int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	CREATESTRUCT cs;
	cs.dwExStyle = 0;
	cs.lpszClass = "STATIC";
	cs.lpszName = strText;
	cs.style = WS_CHILD | WS_VISIBLE;
	cs.x = x;
	cs.y = y;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.hwndParent = hWndParent;
	cs.hMenu = (HMENU)4545;
	cs.hInstance = ghInst;
	cs.lpCreateParams = NULL;

	return 	::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
			cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
			cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
}

HWND CreateBitmap(UINT nBitmapId, int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	CREATESTRUCT cs;
	cs.dwExStyle = 0;
	cs.lpszClass = "STATIC";
	cs.lpszName = "bitmap";
	cs.style = WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE;
	cs.x = x;
	cs.y = y;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.hwndParent = hWndParent;
	cs.hMenu = (HMENU)4545;
	cs.hInstance = ghInst;
	cs.lpCreateParams = NULL;

	HWND hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
			cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
			cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);

	HBITMAP hBitmap = ::LoadBitmap(ghInst, MAKEINTRESOURCE(nBitmapId));
	::SendMessage(hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

	return hWnd;
}

BOOL AddTwoHeaders(HWND hWnd, LPCTSTR strTitle, LPCTSTR strSubtitle)
{
	// insert white header
	HFONT hFont = (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0);
	LOGFONT logFont;
	::GetObject(hFont, sizeof(LOGFONT), &logFont);

	HFONT hFontSubHeader = ::CreateFontIndirect(&logFont);
	logFont.lfWeight = FW_SEMIBOLD;
	HFONT hFontHeader = ::CreateFontIndirect(&logFont);

	ghTitle = CreateStatic(strTitle, 17,11,464,30, hWnd);
	::SendMessage(ghTitle, WM_SETFONT, (WPARAM)hFontHeader, TRUE);

	ghSubTitle = CreateStatic(strSubtitle, 17,33,464,20, hWnd);				// x=17, y=33, 464 wide
	::SendMessage(ghSubTitle, WM_SETFONT, (WPARAM)hFontSubHeader, TRUE);

	HWND hWhiteBanner = ::GetDlgItem(hWnd, IDC_HEADER_PANEL);
	if (hWhiteBanner) {
		::GetWindowRect(hWhiteBanner, &grtWhiteBanner);
		::ScreenToClient(hWnd, (POINT*)(&grtWhiteBanner));
		::ScreenToClient(hWnd, ((POINT*)(&grtWhiteBanner))+1);
		::ShowWindow(hWhiteBanner, SW_HIDE);
	}
	
//	commented because it does not work
//	CreateBitmap(IDB_INSTALL_ICON, 20, 30, 50, 50, hWnd);

	return TRUE;
}

ResourceString::ResourceString(UINT idr)
{
	LoadString(ghInst, idr, m_sz, sizeof(m_sz));
	m_sz[sizeof(m_sz) - 1] = 0;
}

bool GetStringFromResource(int idt, int idr, char *psz, int cb)
{
	HRSRC hr = FindResource(NULL, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(idt));
	if (hr == NULL)
		return false;
	int cbRes = SizeofResource(NULL, hr);
	HGLOBAL h = LoadResource(NULL, hr);
	char *pszRes = (char *)LockResource(h);

	while (cb-- != 0) {
		*psz++ = *pszRes;
		if (*pszRes++ == 0)
			break;
	}
	return true;
}

char *GetTextFileResource(int idr)
{
	HRSRC hr = FindResource(NULL, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(kidtTEXTFILES));
	HGLOBAL h = LoadResource(NULL, hr);
	return (char *)LockResource(h);
}

BOOL CALLBACK WelcomeDlgProc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	switch (wm) {
	case WM_INITDIALOG:
		{
		// Grab the readme.txt resource and stick it in the edit control

		char szDeviceType[30];
		szDeviceType[0] = 0;
		GetStringFromResource(kidtDEVICETYPESTRINGS, kidrDirectory, szDeviceType, sizeof(szDeviceType));

		char szApplicationName[80];
		szApplicationName[0] = 0;
		GetStringFromResource(kidtMISCSTRINGS, kidrDirectory, szApplicationName, sizeof(szApplicationName));
		::SetWindowText(hwnd, szApplicationName);

		SetDlgItemText(hwnd, kidcEdit, GetTextFileResource(kidrReadme));
		char title[1024];
		char subTitle[1024];

		ResourceString strWelcomeTitle(kidrWelcomeTitle);								// Load 'Pocket PC installation'
		sprintf(title, strWelcomeTitle.m_sz, szDeviceType);									// Replace Device Type into %s in kidrWelcomeTitle
		ResourceString strWelcomeSubtitle(kidrWelcomeSubtitle);							// Load '%s will be installed on your Pocket PC now'
		sprintf(subTitle, strWelcomeSubtitle.m_sz, szApplicationName);						// Replace Application Name into %s in strWelcomeSubtitle

		AddTwoHeaders(hwnd, title, subTitle);

		return FALSE;
		}

	case WM_CTLCOLORSTATIC:
		{
			HDC hDC = (HDC)wp;
			HWND hStatis = (HWND)lp;
			if ((hStatis==ghTitle) || (hStatis==ghSubTitle)) {
				::SetBkMode(hDC, TRANSPARENT);
				::SetBkColor(hDC, RGB(0xFF, 0xFF, 0xFF));
				return (BOOL)::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
			} else {
				return FALSE;
			}
		}

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = ::BeginPaint(hwnd, &ps);
			HBRUSH hBrush = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
			::FillRect(hDC, &grtWhiteBanner, hBrush);
			::DeleteObject(hBrush);
			::EndPaint(hwnd, &ps);
			return TRUE;
		}

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
			{
				HWND hParent = ::GetParent(hwnd);
				if (LOWORD(wp)==IDOK) {
					::PostMessage(hParent, WM_FINISH_STEP, WFS_NEXT, 0);
				} else {
					::PostMessage(hParent, WM_FINISH_STEP, WFS_CANCEL, 0);
				}
				break;
			}

		case EN_SETFOCUS:
			// Edit control getting the focus, make sure nothing is selected

			SendDlgItemMessage(hwnd, kidcEdit, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
			break;
		}
		break;
	}

	return FALSE;
}

BOOL WelcomeDialog()
{
	return (BOOL)DialogBox(ghInst, MAKEINTRESOURCE(kiddWelcome), NULL, (DLGPROC)WelcomeDlgProc);
}

BOOL CALLBACK EulaDlgProc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	switch (wm) {
	case WM_INITDIALOG:
		{
		// Grab the eula.txt resource and stick it in the edit control

		SetDlgItemText(hwnd, kidcEdit, GetTextFileResource(kidrEula));

		ResourceString strEulaTitle(kidrEulaTitle);
		ResourceString strEulaSubtitle(kidrEulaSubtitle);
		AddTwoHeaders(hwnd, strEulaTitle.m_sz, strEulaSubtitle.m_sz);

		char szApplicationName[80];
		szApplicationName[0] = 0;
		GetStringFromResource(kidtMISCSTRINGS, kidrDirectory, szApplicationName, sizeof(szApplicationName));
		::SetWindowText(hwnd, szApplicationName);

		HWND hNext = GetDlgItem(hwnd, IDOK);
		::EnableWindow(hNext, FALSE);

		HWND hAccept = GetDlgItem(hwnd, IDC_ACCEPTANCE_NOT);
		::SendMessage(hAccept, BM_SETCHECK, 1, 0);
		return TRUE;
		}

	case WM_CTLCOLORSTATIC:
		{
			HDC hDC = (HDC)wp;
			HWND hStatis = (HWND)lp;
			if ((hStatis==ghTitle) || (hStatis==ghSubTitle)) {
				::SetBkMode(hDC, TRANSPARENT);
				::SetBkColor(hDC, RGB(0xFF, 0xFF, 0xFF));
				return (BOOL)::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
			} else {
				return FALSE;
			}
		}

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = ::BeginPaint(hwnd, &ps);
			HBRUSH hBrush = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
			::FillRect(hDC, &grtWhiteBanner, hBrush);
			::DeleteObject(hBrush);
			::EndPaint(hwnd, &ps);
			return TRUE;
		}

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
			{
			UINT id = LOWORD(wp);
			switch (id) {
			case IDCANCEL:
				{
				HWND hParent = ::GetParent(hwnd);
				::PostMessage(hParent, WM_FINISH_STEP, WFS_CANCEL, 0);
				break;
				}
			case IDOK:
				{
				HWND hParent = ::GetParent(hwnd);
				::PostMessage(hParent, WM_FINISH_STEP, WFS_FINISH, 0);
				break;
				}
			case IDC_BACK:
				{
				HWND hParent = ::GetParent(hwnd);
				::PostMessage(hParent, WM_FINISH_STEP, WFS_PREV, 0);
				break;
				}
			case IDC_ACCEPTANCE:
				{
				HWND hNext = GetDlgItem(hwnd, IDOK);
				if(IsDlgButtonChecked(hwnd, IDC_ACCEPTANCE))
					::EnableWindow(hNext, TRUE);
				break;
				}
			case IDC_ACCEPTANCE_NOT:
				{
				HWND hNext = GetDlgItem(hwnd, IDOK);
				if(IsDlgButtonChecked(hwnd, IDC_ACCEPTANCE_NOT))
					::EnableWindow(hNext, FALSE);
				break;
				}
			}

			break;
			}

		case EN_SETFOCUS:
			// Edit control getting the focus, make sure nothing is selected

			SendDlgItemMessage(hwnd, kidcEdit, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
			break;
		}
		break;
	}

	return FALSE;
}

BOOL EulaDialog()
{
	return (BOOL)DialogBox(ghInst, MAKEINTRESOURCE(kiddEula), NULL, (DLGPROC)EulaDlgProc);
}

BYTE *GetCEAppMgrFilePtr(int idr, int *pcb)
{
	HRSRC hr = FindResource(NULL, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(kidtCEAPPMGRFILES));
	if (hr == NULL)
		return NULL;
	*pcb = SizeofResource(NULL, hr);
	HGLOBAL h = LoadResource(NULL, hr);
	return (BYTE *)LockResource(h);
}

// This function saves a resource from the CEAPPMGRFILES type and saves it as a file
// in the directory szDir. The filename of the file is taking from the String Table
// with the same resource id.
//
// NOTE: A nice feature would be if the bits in CEAPPMGRFILES were compressed. This function
// would be the one to modify to decompress the bits into a file.

BOOL SaveCEAppMgrResToFile(int idr, char *pszDir, BOOL *pfError)
{
	*pfError = FALSE;

	// Get the byte pointer to the bits for this file. If none, we're done.

	int cb;
	BYTE *pb = GetCEAppMgrFilePtr(idr, &cb);
	if (pb == NULL)
		return FALSE;

	// Get the filename of these bits

	char szFn[MAX_PATH];
	if (!GetStringFromResource(kidtCEAPPMGRFILENAMES, idr, szFn, sizeof(szFn))) {
		*pfError = TRUE;
		return FALSE;
	}

	// Create the fully qualified path

	char szFullFn[MAX_PATH];
	lstrcpy(szFullFn, pszDir);
	lstrcat(szFullFn, "\\");
	lstrcat(szFullFn, szFn);

	// Create the file and write these bytes

	HANDLE h = CreateFile(szFullFn, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		*pfError = TRUE;
		return FALSE;
	}
	int cbWritten = 0;
	if (!WriteFile(h, pb, cb, (DWORD *)&cbWritten, NULL) || cb != cbWritten) {
		*pfError = TRUE;
		return FALSE;
	}
	CloseHandle(h);

	return TRUE;
}

void AddUnregisterInformation(LPCTSTR szInstallDir)
{
	LRESULT lr;
	HKEY hUninstall;
	HKEY hKey;

	lr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_QUERY_VALUE|KEY_CREATE_SUB_KEY, &hUninstall);
	if (lr != ERROR_SUCCESS) {
		ResourceString strServicesNotFound(kidrCannotWriteUninstallInformation);
		ResourceString strSetup(kidrStringSetup);
		MessageBox(NULL, strServicesNotFound.m_sz, strSetup.m_sz, MB_OK);
		return;
	}

	char szApplicationName[80];
	szApplicationName[0] = 0;
	GetStringFromResource(kidtMISCSTRINGS, kidrDirectory, szApplicationName, sizeof(szApplicationName));

	lr = RegCreateKey(hUninstall, szApplicationName, &hKey);
	if (lr != ERROR_SUCCESS) {
		RegCloseKey(hUninstall);
		ResourceString strServicesNotFound(kidrCannotWriteUninstallInformation);
		ResourceString strSetup(kidrStringSetup);
		MessageBox(NULL, strServicesNotFound.m_sz, strSetup.m_sz, MB_OK);
		return;
	}

	char szUninstallString[1024];
	sprintf(szUninstallString, "%s\\Uninstall.exe %s", szInstallDir, szApplicationName);

	RegSetValueEx(hKey, "DisplayName", 0, REG_SZ, (PBYTE)szApplicationName, (strlen(szApplicationName) + 1) * sizeof(TCHAR));
	RegSetValueEx(hKey, "UninstallString", 0, REG_SZ, (PBYTE)szUninstallString, (strlen(szUninstallString) + 1) * sizeof(TCHAR));

	RegCloseKey(hKey);
	RegCloseKey(hUninstall);
}

void InstallApp()
{
	// Find the "Windows CE Services" directory. First find the CEAppMgr.exe path.

	LRESULT lr;
	HKEY hkey;

	lr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\CEAPPMGR.EXE", 0, KEY_QUERY_VALUE, &hkey);
	if (lr != ERROR_SUCCESS) {
Error:
		// Error!

		ResourceString strServicesNotFound(kidrStringWinCEServicesNotFound);
		ResourceString strSetup(kidrStringSetup);
		MessageBox(NULL, strServicesNotFound.m_sz, strSetup.m_sz, MB_OK);
		return;
	}

	// Grab the path string

	char szFnAppMgrExe[MAX_PATH];
	DWORD cb;
	cb = sizeof(szFnAppMgrExe);
	lr = RegQueryValueEx(hkey, "", 0, NULL, (BYTE *)szFnAppMgrExe, &cb);
	if (lr != ERROR_SUCCESS)
		goto Error;
	RegCloseKey(hkey);

	// Strip the directory portion off; this is the install directory

	char szDir[MAX_PATH];
	lstrcpy(szDir, szFnAppMgrExe);
	char *pchBack = NULL;
	for (char *pch = szDir; *pch != 0; pch++) {
		if (*pch == '\\')
			pchBack = pch + 1;
	}
	if (pchBack == NULL)
		goto Error;
	*pchBack = 0;

	// Grab the install directory

	char szDirName[80];
	szDirName[0] = 0;
	GetStringFromResource(kidtMISCSTRINGS, kidrDirectory, szDirName, sizeof(szDirName));
	lstrcat(szDir, szDirName);

	// Try to make this directory

	if (!CreateDirectory(szDir, NULL)) {
		if (GetLastError() != ERROR_ALREADY_EXISTS) {
			// Failed creating the directory! Strange error... Assume the path is invalid,
			// probably the directory name from the string table is wrong.

			ResourceString strCouldntCreateInstallDir(kidrStringCouldntCreateInstallDir);
			MessageBox(NULL, strCouldntCreateInstallDir.m_sz, szDir, MB_OK);
			return;
		}
	}

	// Install directory created... now copy the install files into it

	BOOL fError;
	int i = 1;
	while (SaveCEAppMgrResToFile(i, szDir, &fError))
		i++;
	if (fError) {
		// Error occured while saving to disk!

		ResourceString strErrorWritingCEApp(kidrStringErrorWritingCEApp);
		MessageBox(NULL, strErrorWritingCEApp.m_sz, szDir, MB_OK);
		return;
	}

	// Get the full path and filename to the .ini file

	char szIniFile[MAX_PATH];
	lstrcpy(szIniFile, "\"");
	lstrcat(szIniFile, szDir);
	lstrcat(szIniFile, "\\");
	int cch = lstrlen(szIniFile);

	if (!GetStringFromResource(kidtCEAPPMGRFILENAMES, kidrIniFile, &szIniFile[cch], sizeof(szIniFile) - cch)) {
		// Coulding find the kidsIniFile resource

		ResourceString strMissingSetupFiles(kidrStringMissingSetupFiles);
		ResourceString strSetup(kidrStringSetup);
		MessageBox(NULL, strMissingSetupFiles.m_sz, strSetup.m_sz, MB_OK);
		return;
	}
	lstrcat(szIniFile, "\"");

	//Add unregister information
	AddUnregisterInformation(szDir);

	// WinExec it
	char szCmdLine[MAX_PATH];
	lstrcpy(szCmdLine, szFnAppMgrExe);
	lstrcat(szCmdLine, " ");
	lstrcat(szCmdLine, szIniFile);
	WinExec(szCmdLine, SW_SHOW);
}

void main()
{
	char szApplicationName[80];
	szApplicationName[0] = 0;
	GetStringFromResource(kidtMISCSTRINGS, kidrDirectory, szApplicationName, sizeof(szApplicationName));

	CWizard w(ghInst, szApplicationName);
	w.AddStep(kiddWelcome, (DLGPROC)WelcomeDlgProc);
	w.AddStep(kiddEula, (DLGPROC)EulaDlgProc);
	UINT nFinishFlag = w.Run();

	if (nFinishFlag==WFS_FINISH) {
		InstallApp();
	}
}
