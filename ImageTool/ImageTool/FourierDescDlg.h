#pragma once


// CFourierDescDlg ��ȭ �����Դϴ�.

class CFourierDescDlg : public CDialog
{
	DECLARE_DYNAMIC(CFourierDescDlg)

public:
	CFourierDescDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFourierDescDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FOURIER_DESCRIPTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
  int m_nPercent;
};
