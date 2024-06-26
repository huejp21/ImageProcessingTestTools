#pragma once
#include "afxwin.h"


// CArithmeticDlg 대화 상자입니다.

class CArithmeticDlg : public CDialog
{
	DECLARE_DYNAMIC(CArithmeticDlg)

public:
	CArithmeticDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArithmeticDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ARITHMETIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
  CComboBox m_comboImage1;
  CComboBox m_comboImage2;
  int m_nOption;
  void *m_pDoc1;
  void *m_pDoc2;
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedOk();
};
