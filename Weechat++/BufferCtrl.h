#pragma once


// CBufferCtrl

class CBufferCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CBufferCtrl)

public:
	CBufferCtrl();
	virtual ~CBufferCtrl();

protected:
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()

private:
    BOOL RegisterWndClass();
};


