// DiffusionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "DiffusionDlg.h"
#include "afxdialogex.h"


// CDiffusionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDiffusionDlg, CDialogEx)

CDiffusionDlg::CDiffusionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiffusionDlg::IDD, pParent)
  , m_fLambda(0.25f)
  , m_fK(4.f)
  , m_nIteration(10)
{

}

CDiffusionDlg::~CDiffusionDlg()
{
}

void CDiffusionDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_DIFFUSION_LAMBDA, m_fLambda);
  DDX_Text(pDX, IDC_DIFFUSION_K, m_fK);
  DDX_Text(pDX, IDC_DIFFUSION_ITER, m_nIteration);
}


BEGIN_MESSAGE_MAP(CDiffusionDlg, CDialogEx)
END_MESSAGE_MAP()


// CDiffusionDlg 메시지 처리기입니다.
