#pragma once
#include "afxcmn.h"
#include "Dib.h"


// CBinarizarionDlg 대화 상자입니다.

class CBinarizationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinarizationDlg)

public:
  CBinarizationDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
  virtual ~CBinarizationDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BINARIZATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
  CSliderCtrl m_sliderThreshold;
  int m_nThreshold;

  CDib m_DibSrc;
  CDib m_DibRes;
public:
  void SetImage(CDib &dib);
  
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnEnChangeThresholdEdit();
};
