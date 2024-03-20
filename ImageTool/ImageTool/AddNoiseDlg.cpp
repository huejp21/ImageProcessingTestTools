// AddNoiseDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "AddNoiseDlg.h"
#include "afxdialogex.h"


// CAddNoiseDlg ��ȭ �����Դϴ�.

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


// CAddNoiseDlg �޽��� ó�����Դϴ�.


BOOL CAddNoiseDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
  m_sliderNoise.SetRange(0, 100);
  m_sliderNoise.SetTicFreq(20);
  m_sliderNoise.SetPageSize(20);
  m_sliderNoise.SetPos(m_nAmount);
  return TRUE;  // return TRUE unless you set the focus to a control
  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CAddNoiseDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
  // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
  // CDialog::OnInitDialog() �Լ��� ������ 
  //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
  // �� �˸� �޽����� ������ �ʽ��ϴ�.

  // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  UpdateData(TRUE);
  m_sliderNoise.SetPos(m_nAmount);
}
