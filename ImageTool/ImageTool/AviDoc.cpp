// AviDoc.cpp : 구현 파일입니다.
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


// CAviDoc 진단입니다.

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
// CAviDoc serialization입니다.

void CAviDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}
#endif


// CAviDoc 명령입니다.


void CAviDoc::OnFileNew()
{
  // TODO: 여기에 명령 처리기 코드를 추가합니다.
  theApp.m_pImageDocTemplate->OpenDocumentFile(NULL);
}


BOOL CAviDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
  // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
  //return CDocument::OnSaveDocument(lpszPathName);
  return FALSE;
}


BOOL CAviDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
  if (!CDocument::OnOpenDocument(lpszPathName))
    return FALSE;

  // TODO:  여기에 특수화된 작성 코드를 추가합니다.
  POSITION pos = GetFirstViewPosition();
  if (pos != NULL)
  {
    CAviView *pView = (CAviView*)GetNextView(pos);
    pView->AviFileOpen(lpszPathName);
  }
  return TRUE;
}
