// GaussianDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "GaussianDlg.h"
#include "afxdialogex.h"


// CGaussianDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGaussianDlg, CDialog)

CGaussianDlg::CGaussianDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGaussianDlg::IDD, pParent)
  , m_fSigma(0)
{

}

CGaussianDlg::~CGaussianDlg()
{
}

void CGaussianDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SIGMA_SLIDER, m_sliderSigma);
  DDX_Text(pDX, IDC_SIGMA_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0.20f, 5.00f);
}


BEGIN_MESSAGE_MAP(CGaussianDlg, CDialog)
  ON_WM_HSCROLL()
  ON_EN_CHANGE(IDC_SIGMA_EDIT, &CGaussianDlg::OnEnChangeSigmaEdit)
END_MESSAGE_MAP()


// CGaussianDlg 메시지 처리기입니다.


BOOL CGaussianDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  m_sliderSigma.SetRange(10, 250);
  m_sliderSigma.SetTicFreq(20);
  m_sliderSigma.SetPageSize(20);
  m_sliderSigma.SetPos((int)(m_fSigma * 50));
  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGaussianDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
  if (m_sliderSigma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
  {
    int pos = m_sliderSigma.GetPos();
    m_fSigma = (pos / 50.f);
    UpdateData(FALSE);
  }
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGaussianDlg::OnEnChangeSigmaEdit()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  UpdateData(TRUE);
  m_sliderSigma.SetPos((int)(m_fSigma * 50));
}
