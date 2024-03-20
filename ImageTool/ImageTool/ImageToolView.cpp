
// ImageToolView.cpp : CImageToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CImageToolView ����/�Ҹ�

CImageToolView::CImageToolView()
  : m_nZoom(1)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageToolView::~CImageToolView()
{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView �׸���

//void CImageToolView::OnDraw(CDC* /*pDC*/)
void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

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


	//// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
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

// CImageToolView �μ�

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CImageToolView ����

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView �޽��� ó����


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

  //return CScrollView::OnEraseBkgnd(pDC);

  CBrush br;
  br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
  FillOutsideRect(pDC, &br);
  return TRUE;
}


void CImageToolView::OnViewZoom1()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  m_nZoom = 1;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom2()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  m_nZoom = 2;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom3()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  m_nZoom = 3;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnViewZoom4()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  m_nZoom = 4;
  SetScrollSizeToFit();
  Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->SetCheck(m_nZoom == 1);
}


void CImageToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->SetCheck(m_nZoom == 2);
}


void CImageToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->SetCheck(m_nZoom == 3);
}


void CImageToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->SetCheck(m_nZoom == 4);
}


void CImageToolView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

