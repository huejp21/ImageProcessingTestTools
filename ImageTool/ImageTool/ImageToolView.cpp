
// ImageToolView.cpp : CImageToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"
#include "ImageToolView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolView

IMPLEMENT_DYNCREATE(CImageToolView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
  ON_WM_ERASEBKGND()
  ON_COMMAND(ID_VIEW_ZOOM1, &CImageToolView::OnViewZoom1)
  ON_COMMAND(ID_VIEW_ZOOM2, &CImageToolView::OnViewZoom2)
  ON_COMMAND(ID_VIEW_ZOOM3, &CImageToolView::OnViewZoom3)
  ON_COMMAND(ID_VIEW_ZOOM4, &CImageToolView::OnViewZoom4)
  ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageToolView::OnUpdateViewZoom1)
  ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageToolView::OnUpdateViewZoom2)
  ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageToolView::OnUpdateViewZoom3)
  ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageToolView::OnUpdateViewZoom4)
  ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CImageToolView 생성/소멸

CImageToolView::CImageToolView()
  : m_nZoom(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageToolView::~CImageToolView()
{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView 그리기

//void CImageToolView::OnDraw(CDC* /*pDC*/)
void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

  if (pDoc->m_Dib.IsValid())
  {
    int w = pDoc->m_Dib.GetWidth();
    int h = pDoc->m_Dib.GetHeight();
    pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w*m_nZoom, h*m_nZoom);
    //pDoc->m_Dib.Draw(pDC->m_hDC);
  }
}

void CImageToolView::OnInitialUpdate()
{
	//CScrollView::OnInitialUpdate();

	//CSize sizeTotal;


	//// TODO: 이 뷰의 전체 크기를 계산합니다.
	//sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);

  CScrollView::OnInitialUpdate();
  SetScrollSizeToFit();
 
}

void CImageToolView::SetScrollSizeToFit(void)
{
  CSize sizeTotal;
  CImageToolDoc *pDoc = GetDocument();
  if (pDoc->m_Dib.IsValid())
  {
    int w = pDoc->m_Dib.GetWidth();
    int h = pDoc->m_Dib.GetHeight();

    sizeTotal.cx = pDoc->m_Dib.GetWidth();
    sizeTotal.cy = pDoc->m_Dib.GetHeight();
  }
  else
  {
    sizeTotal.cx = sizeTotal.cy = 100;
  }
  SetScrollSizes(MM_TEXT, sizeTotal);
  ResizeParentToFit(TRUE);
}

// CImageToolView 인쇄

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageToolView 진단

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView 메시지 처리기


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

  //return CScrollView::OnEraseBkgnd(pDC);

  CBrush br;
  br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
  FillOutsideRect(pDC, &br);
  return TRUE;
}


void CImageToolView::OnViewZoom1()
{
  // TODO: 여기에 명령 처리기 코드를 추가합니다.
  m_nZoom = 1;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom2()
{
  // TODO: 여기에 명령 처리기 코드를 추가합니다.
  m_nZoom = 2;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom3()
{
  // TODO: 여기에 명령 처리기 코드를 추가합니다.
  m_nZoom = 3;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom4()
{
  // TODO: 여기에 명령 처리기 코드를 추가합니다.
  m_nZoom = 4;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
  // TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
  pCmdUI->SetCheck(m_nZoom == 1);
}


void CImageToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
  // TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
  pCmdUI->SetCheck(m_nZoom == 2);
}


void CImageToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
  // TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
  pCmdUI->SetCheck(m_nZoom == 3);
}


void CImageToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
  // TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
  pCmdUI->SetCheck(m_nZoom == 4);
}


void CImageToolView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
  CPoint pt = point + GetScrollPosition();
  pt.x /= m_nZoom;
  pt.y /= m_nZoom;
  ShowImageInfo(pt);
  CScrollView::OnMouseMove(nFlags, point);
}

void CImageToolView::ShowImageInfo(CPoint point)
{
  CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
  CImageToolDoc *pDoc = GetDocument();
  int w = pDoc->m_Dib.GetWidth();
  int h = pDoc->m_Dib.GetHeight();
  int c = pDoc->m_Dib.getPaletteNums();
  CString strText;

  if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
  {
    strText.Format(TEXT("(%d, %d)"), point.x, point.y);
    pFrame->m_wndStatusBar.SetPaneText(0, strText);
  }

  if (c == 0)
  {
    strText.Format(TEXT("Width:%d Height:%d C:16M"), w, h);
  }
  else
  {
    strText.Format(TEXT("Width:%d Height:%d C:%d"), w, h, c);
  }
  pFrame->m_wndStatusBar.SetPaneText(1, strText);
}

