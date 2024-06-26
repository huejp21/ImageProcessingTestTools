#pragma once


// CFileNewDlg 대화 상자입니다.

class CFileNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileNewDlg)

public:
	CFileNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FILE_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
  int m_nWidth;
  int m_nHeight;
  int m_nType;
  afx_msg void OnBnClickedOk();
};
