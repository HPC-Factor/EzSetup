#ifndef __wiard_h__
#define __wiard_h__

#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define WFS_NEXT 0
#define WFS_PREV 1
#define WFS_FINISH 2
#define WFS_CANCEL 3
#define WFS_CUSTOM 100

#define MAX_STEP_COUNT 10000

#define WM_FINISH_STEP (WM_USER+1)

struct CWizardStep
{
	UINT m_nDialogId;
	DLGPROC m_lpDialogFunc;
};


class CWizard
{
public:
	CWizard(HINSTANCE hInst, LPCTSTR szTitle);
	~CWizard();
	void OnInitWizard(HWND hWnd);

	void AddStep(UINT nDialogId, DLGPROC lpDialogFunc);
	UINT Run();

	void SetStep(UINT nStepIndex);
	UINT GetCurStepIndex();
	void NextStep();
	void PrevStep();
	void FinishWizard();
	void CancelWizard();


//private:
public:
	CWizardStep m_steps[MAX_STEP_COUNT];

	LPCTSTR m_szTitle;
	HINSTANCE m_hInst;
	HWND m_hCurStepWnd;
	UINT m_nCurStep;
	UINT m_nStepsCount;
	HWND m_hWnd;
};


#endif /*__wiard_h__*/