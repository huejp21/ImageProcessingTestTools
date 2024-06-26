// HistogramDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"
#include "DibEnhancement.h"


// CHistogramDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialog)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramDlg::IDD, pParent)
{

}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
  ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기입니다.

void CHistogramDlg::SetImage(CDib &dib)
{
  float histo[256] = { 0.f, };
  DibHistogram(dib, histo);

  float max_value = histo[0];
  for (register int i = 1; i < 256; i++)
  {
    if (histo[i] > max_value) max_value = histo[i];
  }
  for (register int i = 0; i < 256; i++)
  {
    m_Histogram[i] = (int)(histo[i] * 100 / max_value);
  }
}

void CHistogramDlg::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  // TODO: 여기에 메시지 처리기 코드를 추가합니다.
  // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
  dc.MoveTo(20, 30);
  dc.LineTo(20, 130);
  dc.LineTo(275, 130);
  dc.LineTo(275, 30);
  for (register int i = 0; i < 256; i++)
  {
    dc.MoveTo(20 + i, 130);
    dc.LineTo(20 + i, 130 - m_Histogram[i]);
  }
  for (register int i = 0; i < 256; i++)
  {
    dc.SelectStockObject(DC_PEN);
    dc.SetDCPenColor(RGB(i, i, i));
    dc.MoveTo(20 + i, 140);
    dc.LineTo(20 + i, 155);
  }
}
