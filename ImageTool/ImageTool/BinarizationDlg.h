#pragma once
#include "afxcmn.h"
#include "Dib.h"


// CBinarizarionDlg ��ȭ �����Դϴ�.

class CBinarizationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinarizationDlg)

public:
  CBinarizationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
  virtual ~CBinarizationDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BINARIZATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
