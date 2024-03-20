// FourierDescDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FourierDescDlg.h"
#include "afxdialogex.h"


// CFourierDescDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFourierDescDlg, CDialog)

CFourierDescDlg::CFourierDescDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFourierDescDlg::IDD, pParent)
  , m_nPercent(100)
{

}

CFourierDescDlg::~CFourierDescDlg()
{
}

void CFourierDescDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_PERCENT, m_nPercent);
}


BEGIN_MESSAGE_MAP(CFourierDescDlg, CDialog)
END_MESSAGE_MAP()


// CFourierDescDlg 메시지 처리기입니다.
