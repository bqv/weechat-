#pragma once


// CInputCtrl

class CInputCtrl : public CEdit
{
	DECLARE_DYNAMIC(CInputCtrl)

public:
	CInputCtrl();
	virtual ~CInputCtrl();

protected:
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()

private:
    BOOL RegisterWndClass();
};


