#pragma once

#define REG_SECTION_LOGIN _T("Login")
#define REG_ENTRY_TYPE _T("Type")
#define REG_ENTRY_HOST _T("Host")
#define REG_ENTRY_PORT _T("Port")
#define REG_ENTRY_PASS _T("Password")

// CConnectDlg dialog

class CConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CConnectDlg();

    afx_msg void OnOK();

    int m_relayType;
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
