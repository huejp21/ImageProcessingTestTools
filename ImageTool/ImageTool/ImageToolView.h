
// ImageToolView.h : CImageToolView 클래스의 인터페이스
//

#pragma once


class CImageToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageToolView();
	DECLARE_DYNCREATE(CImageToolView)

// 특성입니다.
public:
	CImageToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  void SetScrollSizeToFit(void);
  void ShowImageInfo(CPoint point);

// 구현입니다.
public:
	virtual ~CImageToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  int m_nZoom;
  afx_msg void OnViewZoom1();
  afx_msg void OnViewZoom2();
  afx_msg void OnViewZoom3();
  afx_msg void OnViewZoom4();
  afx_msg void OnUpdateViewZoom1(CCmdUI *pCmdUI);
  afx_msg void OnUpdateViewZoom2(CCmdUI *pCmdUI);
  afx_msg void OnUpdateViewZoom3(CCmdUI *pCmdUI);
  afx_msg void OnUpdateViewZoom4(CCmdUI *pCmdUI);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ImageToolView.cpp의 디버그 버전
inline CImageToolDoc* CImageToolView::GetDocument() const
   { return reinterpret_cast<CImageToolDoc*>(m_pDocument); }
#endif

