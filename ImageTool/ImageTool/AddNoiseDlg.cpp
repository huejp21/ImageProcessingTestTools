// AddNoiseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "AddNoiseDlg.h"
#include "afxdialogex.h"


// CAddNoiseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialog)

CAddNoiseDlg::CAddNoiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNoiseDlg::IDD, pParent)
  , m_nNoiseType(0)
  , m_nAmount(10)
{

}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_NOISE_RADIO0, m_nNoiseType);
  DDX_Text(pDX, IDC_NOISE_AMOUNT, m_nAmount);
  DDV_MinMaxInt(pDX, m_nAmount, 0, 100);
  DDX_Control(pDX, IDC_NOISE_SLIDER, m_sliderNoise);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialog)
  ON_WM_HSCROLL()
  ON_EN_CHANGE(IDC_NOISE_AMOUNT, &CAddNoiseDlg::OnEnChangeNoiseAmount)
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기입니다.


BOOL CAddNoiseDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  m_sliderNoise.SetRange(0, 100);
  m_sliderNoise.SetTicFreq(20);
  m_sliderNoise.SetPageSize(20);
  m_sliderNoise.SetPos(m_nAmount);
  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddNoiseDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
  if (m_sliderNoise.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
  {
    int pos = m_sliderNoise.GetPos();
    m_nAmount = pos;
    UpdateData(FALSE);
  }
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAddNoiseDlg::OnEnChangeNoiseAmount()
{
  // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
  // CDialog::OnInitDialog() 함수를 재지정 
  //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
  // 이 알림 메시지를 보내지 않습니다.

  // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
  UpdateData(TRUE);
  m_sliderNoise.SetPos(m_nAmount);
}
