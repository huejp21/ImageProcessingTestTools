// FourierDescDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "FourierDescDlg.h"
#include "afxdialogex.h"


// CFourierDescDlg ��ȭ �����Դϴ�.

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


// CFourierDescDlg �޽��� ó�����Դϴ�.
