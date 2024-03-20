#pragma once
#include "afxcmn.h"


// CContrastDlg 대화 상자입니다.

class CContrastDlg : public CDialog
{
	DECLARE_DYNAMIC(CContrastDlg)

public:
	CContrastDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CContrastDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
  CSliderCtrl m_sliderContrast;
  int m_nContrast;
  virtual BOOL OnInitDialog();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnEnChangeContrastEdit();
};
