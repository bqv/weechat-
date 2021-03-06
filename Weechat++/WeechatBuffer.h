
// WeechatBuffer.h : interface of the CWeechatBuffer class
//

#pragma once

#include "BufferLine.h"
#include "Relay/Handler.h"

class CWeechatBuffer : public CDocument
{
//protected: // create from serialization only
public:
	CWeechatBuffer();
    CWeechatBuffer(const CWeechatBuffer& other);
	DECLARE_DYNCREATE(CWeechatBuffer)

// Attributes
public:
    CString m_pointer;
    int m_number;
    CString m_name;
    CString m_fullName;
    CString m_shortName;
    BOOL m_hasNicklist;
    CString m_title;
    CMap<CString, LPCTSTR, CString, const CString&> m_localVariables;
    CString m_prevBuffer;
    CString m_nextBuffer;
    int m_type;

// Operations
public:
    void AddLine(const CBufferLine& line);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
    CWeechatBuffer operator=(const CWeechatBuffer& other);
	virtual ~CWeechatBuffer();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
