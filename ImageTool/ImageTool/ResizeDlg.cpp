// ResizeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CResizeDlg, CDialog)

CResizeDlg::CResizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResizeDlg::IDD, pParent)
  , m_nOldWidth(0)
  , m_nOldHeight(0)
  , m_nNewWidth(0)
  , m_nNewHeight(0)
  , m_bAspectRatio(FALSE)
  , m_nInterpolation(0)
{

}

CResizeDlg::~CResizeDlg()
{
}

void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_OLD_WIDTH, m_nOldWidth);
  DDX_Text(pDX, IDC_OLD_HEIGHT, m_nOldHeight);
  DDX_Text(pDX, IDC_NEW_WIDTH, m_nNewWidth);
  DDX_Text(pDX, IDC_NEW_HEIGHT, m_nNewHeight);
  DDX_Check(pDX, IDC_ASPECT_RATIO, m_bAspectRatio);
  DDX_CBIndex(pDX, IDC_INTERPOLATION, m_nInterpolation);
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialog)
  ON_EN_CHANGE(IDC_NEW_WIDTH, &CResizeDlg::OnEnChangeNewWidth)
  ON_EN_CHANGE(IDC_NEW_HEIGHT, &CResizeDlg::OnEnChangeNewHeight)
  ON_BN_CLICKED(IDC_ASPECT_RATIO, &CResizeDlg::OnBnClickedAspectRatio)
END_MESSAGE_MAP()


// CResizeDlg 메시지 처리기입니다.


void CResizeDlg::OnEnChangeNewWidth()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  if (GetDlgItem(IDC_INTERPOLATION)->GetSafeHwnd() == NULL)
  {
    return;
  }
  if (m_bAspectRatio)
  {
    UpdateData(TRUE);
    m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
    UpdateData(FALSE);
  }
}


void CResizeDlg::OnEnChangeNewHeight()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  if (GetDlgItem(IDC_INTERPOLATION)->GetSafeHwnd() == NULL)
  {
    return;
  }
  if (m_bAspectRatio)
  {
    UpdateData(TRUE);
    m_nNewWidth = m_nNewHeight * m_nOldWidth / m_nOldHeight;
    UpdateData(FALSE);
  }
}


void CResizeDlg::OnBnClickedAspectRatio()
{
  // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
  UpdateData(TRUE);
  if (m_bAspectRatio)
  {
    m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
    UpdateData(FALSE);
  }
}


BOOL CResizeDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  m_nNewWidth = m_nOldWidth;
  m_nNewHeight = m_nOldHeight;
  ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_WIDTH))->SetRange(1, 2048);
  ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_HEIGHT))->SetRange(1, 2048);

  UpdateData(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
