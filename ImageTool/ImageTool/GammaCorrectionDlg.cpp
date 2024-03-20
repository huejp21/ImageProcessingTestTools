// GammaCorrectionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "GammaCorrectionDlg.h"
#include "afxdialogex.h"


// CGammaCorrectionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGammaCorrectionDlg, CDialog)

CGammaCorrectionDlg::CGammaCorrectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGammaCorrectionDlg::IDD, pParent)
  , m_fGamma(0)
{

}

CGammaCorrectionDlg::~CGammaCorrectionDlg()
{
}

void CGammaCorrectionDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_GAMMA_SLIDER, m_sliderGamma);
  DDX_Text(pDX, IDC_GAMMA_EDIT, m_fGamma);
  DDV_MinMaxFloat(pDX, m_fGamma, 0.20f, 5.00f);
}


BEGIN_MESSAGE_MAP(CGammaCorrectionDlg, CDialog)
  ON_WM_HSCROLL()
  ON_EN_CHANGE(IDC_GAMMA_EDIT, &CGammaCorrectionDlg::OnEnChangeGammaEdit)
END_MESSAGE_MAP()


// CGammaCorrectionDlg 메시지 처리기입니다.


BOOL CGammaCorrectionDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  m_sliderGamma.SetRange(10, 250);
  m_sliderGamma.SetTicFreq(20);
  m_sliderGamma.SetPageSize(20);
  m_sliderGamma.SetPos((int)(m_fGamma * 50));
  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGammaCorrectionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
  if (m_sliderGamma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
  {
    int pos = m_sliderGamma.GetPos();
    m_fGamma = (pos / 50.f);
    UpdateData(FALSE);
  }
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGammaCorrectionDlg::OnEnChangeGammaEdit()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  UpdateData(TRUE);
  m_sliderGamma.SetPos((int)(m_fGamma * 50));
}
