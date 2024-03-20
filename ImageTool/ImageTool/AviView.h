#pragma once

#include "Avi.h"


// CAviView ���Դϴ�.

class CAviView : public CScrollView
{
	DECLARE_DYNCREATE(CAviView)

protected:
	CAviView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAviView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
  CAvi m_Avi;
  int m_nCurrentFrame;

  BOOL AviFileOpen(LPCTSTR lpszPathName);
protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
};


