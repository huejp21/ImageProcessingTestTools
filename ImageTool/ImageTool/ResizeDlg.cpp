// ResizeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "ResizeDlg.h"
#include "afxdialogex.h"


// CResizeDlg ��ȭ �����Դϴ�.

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


// CResizeDlg �޽��� ó�����Դϴ�.


void CResizeDlg::OnEnChangeNewWidth()
{
  // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
  // CDialog::OnInitDialog() �Լ��� ������ 
  //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
  // �� �˸� �޽����� ������ �ʽ��ϴ�.

  // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
  // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
  // CDialog::OnInitDialog() �Լ��� ������ 
  //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
  // �� �˸� �޽����� ������ �ʽ��ϴ�.

  // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
  // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

  // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
  m_nNewWidth = m_nOldWidth;
  m_nNewHeight = m_nOldHeight;
  ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_WIDTH))->SetRange(1, 2048);
  ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_HEIGHT))->SetRange(1, 2048);

  UpdateData(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
