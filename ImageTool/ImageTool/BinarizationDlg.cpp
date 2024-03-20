// BinarizarionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "BinarizationDlg.h"
#include "afxdialogex.h"

#include "DibGeometry.h"
#include "DibSegment.h"


// CBinarizarionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBinarizationDlg, CDialog)

CBinarizationDlg::CBinarizationDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBinarizationDlg::IDD, pParent)
  , m_nThreshold(0)
{

}

CBinarizationDlg::~CBinarizationDlg()
{
}

void CBinarizationDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_sliderThreshold);
  DDX_Text(pDX, IDC_THRESHOLD_EDIT, m_nThreshold);
}


BEGIN_MESSAGE_MAP(CBinarizationDlg, CDialog)
  ON_WM_PAINT()
  ON_WM_HSCROLL()
  ON_EN_CHANGE(IDC_THRESHOLD_EDIT, &CBinarizationDlg::OnEnChangeThresholdEdit)
END_MESSAGE_MAP()


void CBinarizationDlg::SetImage(CDib &dib)
{
  m_DibSrc = dib;
}

// CBinarizarionDlg �޽��� ó�����Դϴ�.


BOOL CBinarizationDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
  m_sliderThreshold.SetRange(0, 255);
  m_sliderThreshold.SetTicFreq(32);
  m_sliderThreshold.SetPageSize(32);
  m_sliderThreshold.SetPos(m_nThreshold);

  CWnd *pImageWnd = GetDlgItem(IDC_IMAGE_WND);

  CRect rect;
  pImageWnd->GetClientRect(rect);

  DibResizeNearest(m_DibSrc, rect.Width(), rect.Height());

  m_DibRes = m_DibSrc;
  DibBinarization(m_DibRes, m_nThreshold);
  return TRUE;  // return TRUE unless you set the focus to a control
  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBinarizationDlg::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
  // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.

  CPaintDC dc2(GetDlgItem(IDC_IMAGE_WND));
  m_DibRes.Draw(dc2.m_hDC, 0, 0);
}


void CBinarizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
  if (m_sliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
  {
    int pos = m_sliderThreshold.GetPos();
    m_nThreshold = pos;
    UpdateData(FALSE);

    m_DibRes = m_DibSrc;
    DibBinarization(m_DibRes, m_nThreshold);
    Invalidate(FALSE);
  }

  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBinarizationDlg::OnEnChangeThresholdEdit()
{
  // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
  // CDialog::OnInitDialog() �Լ��� ������ 
  //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
  // �� �˸� �޽����� ������ �ʽ��ϴ�.

  // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  UpdateData(TRUE);
  m_sliderThreshold.SetPos(m_nThreshold);

  m_DibRes = m_DibSrc;
  DibBinarization(m_DibSrc, m_nThreshold);
  Invalidate(FALSE);
}
