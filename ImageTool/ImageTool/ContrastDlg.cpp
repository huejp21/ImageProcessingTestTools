// ContrastDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "ContrastDlg.h"
#include "afxdialogex.h"


// CContrastDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CContrastDlg, CDialog)

CContrastDlg::CContrastDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContrastDlg::IDD, pParent)
  , m_nContrast(0)
{

}

CContrastDlg::~CContrastDlg()
{
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
  DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialog)
  ON_WM_HSCROLL()
  ON_EN_CHANGE(IDC_CONTRAST_EDIT, &CContrastDlg::OnEnChangeContrastEdit)
END_MESSAGE_MAP()


// CContrastDlg 메시지 처리기입니다.


BOOL CContrastDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  m_sliderContrast.SetRange(-100, 100);
  m_sliderContrast.SetTicFreq(20);
  m_sliderContrast.SetPageSize(20);
  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
  if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
  {
    int pos = m_sliderContrast.GetPos();
    m_nContrast = pos;
    UpdateData(FALSE);
  }
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CContrastDlg::OnEnChangeContrastEdit()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  UpdateData(TRUE);
  m_sliderContrast.SetPos(m_nContrast);
}
