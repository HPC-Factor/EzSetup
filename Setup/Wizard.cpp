#include "Wizard.h"

CWizard *pWizard = NULL;

CWizard::CWizard(HINSTANCE hInst, LPCTSTR szTitle)
	: m_hInst(hInst),
	  m_hCurStepWnd(NULL),
	  m_nCurStep(0),
	  m_nStepsCount(0),
	  m_szTitle(szTitle)
{
	pWizard = this;
}

CWizard::~CWizard()
{
	pWizard = NULL;
}

void CWizard::AddStep(UINT nDialogId, DLGPROC lpDialogFunc)
{
	m_steps[m_nStepsCount].m_nDialogId = nDialogId;
	m_steps[m_nStepsCount].m_lpDialogFunc = lpDialogFunc;
	m_nStepsCount++;
}


BOOL CALLBACK WizardDlgProc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	switch (wm) {
	case WM_INITDIALOG:
		{
			pWizard->OnInitWizard(hwnd);
			return TRUE;
		}

	case WM_FINISH_STEP:
		{
			switch ((UINT)wp) {
			case WFS_NEXT:
				pWizard->NextStep();
				break;
			case WFS_PREV:
				pWizard->PrevStep();
				break;
			case WFS_FINISH:
				pWizard->FinishWizard();
				break;
			case WFS_CANCEL:
				pWizard->CancelWizard();
				break;
			}
		}

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
			{
				::PostMessage(pWizard->m_hCurStepWnd, wm, wp, lp);
				break;
			}
		}
		break;
	}

	return FALSE;
}

UINT CWizard::Run()
{
	return DialogBox(m_hInst, MAKEINTRESOURCE(IDD_WIZARD), NULL, (DLGPROC)WizardDlgProc);
}

void CWizard::SetStep(UINT nStepIndex)
{
	HWND hDialog = CreateDialog(
		m_hInst, 
		MAKEINTRESOURCE(m_steps[m_nCurStep].m_nDialogId), 
		m_hWnd, 
		m_steps[m_nCurStep].m_lpDialogFunc
	);

	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	::SetWindowPos(hDialog, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);

	if (m_hCurStepWnd!=NULL) {
		::DestroyWindow(m_hCurStepWnd);
	}

	m_hCurStepWnd = hDialog;
}

UINT CWizard::GetCurStepIndex()
{
	return m_nCurStep;
}

void CWizard::NextStep()
{
	m_nCurStep ++;
	if (m_nCurStep>=m_nStepsCount) {
		m_nCurStep = m_nStepsCount-1;
	}
	SetStep(m_nCurStep);
}

void CWizard::PrevStep()
{
	m_nCurStep --;
	if (m_nCurStep<0) {
		m_nCurStep = 0;
	}
	SetStep(m_nCurStep);
}

void CWizard::FinishWizard()
{
	EndDialog(m_hWnd, WFS_FINISH);
}

void CWizard::CancelWizard()
{
	EndDialog(m_hWnd, WFS_CANCEL);
}

void CWizard::OnInitWizard(HWND hWnd)
{
	m_hWnd = hWnd;
	::SetWindowText(hWnd, m_szTitle);
	SetStep(0);
}
