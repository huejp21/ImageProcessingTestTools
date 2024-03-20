// AviDoc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageTool.h"
#include "AviDoc.h"
#include "AviView.h"

// CAviDoc

IMPLEMENT_DYNCREATE(CAviDoc, CDocument)

CAviDoc::CAviDoc()
{
}

BOOL CAviDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;
	//return TRUE;
  return FALSE;
}

CAviDoc::~CAviDoc()
{
}


BEGIN_MESSAGE_MAP(CAviDoc, CDocument)
  ON_COMMAND(ID_FILE_NEW, &CAviDoc::OnFileNew)
END_MESSAGE_MAP()


// CAviDoc �����Դϴ�.

#ifdef _DEBUG
void CAviDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CAviDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CAviDoc serialization�Դϴ�.

void CAviDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}
#endif


// CAviDoc ����Դϴ�.


void CAviDoc::OnFileNew()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  theApp.m_pImageDocTemplate->OpenDocumentFile(NULL);
}


BOOL CAviDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
  // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
  //return CDocument::OnSaveDocument(lpszPathName);
  return FALSE;
}


BOOL CAviDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
  if (!CDocument::OnOpenDocument(lpszPathName))
    return FALSE;

  // TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
  POSITION pos = GetFirstViewPosition();
  if (pos != NULL)
  {
    CAviView *pView = (CAviView*)GetNextView(pos);
    pView->AviFileOpen(lpszPathName);
  }
  return TRUE;
}
