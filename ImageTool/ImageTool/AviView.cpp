// AviView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "AviView.h"


// CAviView

IMPLEMENT_DYNCREATE(CAviView, CScrollView)

CAviView::CAviView()
{
  m_nCurrentFrame = 0;
}

CAviView::~CAviView()
{
}


BEGIN_MESSAGE_MAP(CAviView, CScrollView)
END_MESSAGE_MAP()


// CAviView 그리기입니다.

void CAviView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
  if (m_Avi.IsValid())
  {
    sizeTotal.cx = m_Avi.GetWidth();
    sizeTotal.cy = m_Avi.GetHeight();
  }
  else
  {
    sizeTotal.cx = sizeTotal.cy = 100;
  }
	SetScrollSizes(MM_TEXT, sizeTotal);

  ResizeParentToFit(TRUE);
}

void CAviView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
  if (m_Avi.IsValid())
  {
    m_Avi.DrawFrame(pDC->m_hDC, m_nCurrentFrame);
  }
}


// CAviView 진단입니다.

#ifdef _DEBUG
void CAviView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CAviView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAviView 메시지 처리기입니다.
BOOL CAviView::AviFileOpen(LPCTSTR lpszPathName)
{
  if (!m_Avi.Open(lpszPathName))
  {
    AfxMessageBox(TEXT("Can not Open Avi File!"));
    return FALSE;
  }
  m_nCurrentFrame = 0;
  return TRUE;
}
