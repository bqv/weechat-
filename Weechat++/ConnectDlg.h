#pragma once


// CConnectDlg dialog

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CConnectDlg();

    afx_msg void OnOK();

    CString m_connType;
    CString m_relayHost;
    UINT m_relayPort;
    CString m_relayPass;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
