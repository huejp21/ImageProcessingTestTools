// FileNewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FileNewDlg.h"
#include "afxdialogex.h"


// CFileNewDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFileNewDlg, CDialog)

CFileNewDlg::CFileNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNewDlg::IDD, pParent)
  , m_nWidth(256)
  , m_nHeight(256)
  , m_nType(0)
{

}

CFileNewDlg::~CFileNewDlg()
{
}

void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
  DDV_MinMaxInt(pDX, m_nWidth, 0, 2048);
  DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
  DDV_MinMaxInt(pDX, m_nHeight, 0, 2048);
  DDX_CBIndex(pDX, IDC_COMBO_IMAGETYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CFileNewDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileNewDlg �޽��� ó�����Դϴ�.


void CFileNewDlg::OnBnClickedOk()
{
  // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  CDialog::OnOK();
}
