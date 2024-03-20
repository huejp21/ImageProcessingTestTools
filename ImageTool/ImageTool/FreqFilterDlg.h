#pragma once


// CFreqFilterDlg 대화 상자입니다.

class CFreqFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CFreqFilterDlg)

public:
	CFreqFilterDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFreqFilterDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FREQUENCY_FILTERING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
  CString m_strFilterType;
  CString m_strFilterShape;
  int m_nCutoff;
  CString m_strRange;
};
