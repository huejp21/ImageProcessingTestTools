
// ImageTool.h : ImageTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CImageToolApp:
// �� Ŭ������ ������ ���ؼ��� ImageTool.cpp�� �����Ͻʽÿ�.
//
class CDib;
class CImageToolApp : public CWinApp
{
public:
	CImageToolApp();
  ~CImageToolApp();

public:
  CMultiDocTemplate *m_pImageDocTemplate;
  CMultiDocTemplate *m_pAviDocTemplate;
  CDib *m_pNewDib;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
  afx_msg void OnEditPaste();
  afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
  afx_msg void OnWindowCloseall();
};

extern CImageToolApp theApp;

void AfxNewImage(CDib &dib);