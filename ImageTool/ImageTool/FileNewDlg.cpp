// FileNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FileNewDlg.h"
#include "afxdialogex.h"


// CFileNewDlg 대화 상자입니다.

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


// CFileNewDlg 메시지 처리기입니다.


void CFileNewDlg::OnBnClickedOk()
{
  // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
  CDialog::OnOK();
}
