// HistogramDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"
#include "DibEnhancement.h"


// CHistogramDlg ��ȭ �����Դϴ�.

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


// CHistogramDlg �޽��� ó�����Դϴ�.

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
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
  // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
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
