#pragma once

// CBufferLine command target

struct CBufferLine : CObject
{
	CBufferLine();
	virtual ~CBufferLine();
    CBufferLine& operator=(const CBufferLine& other);

// Attributes
    CTime date;
    CTime datePrinted;
    BOOL displayed;
    BOOL highlight;
    CList<CString> tagsArray;
    CString prefix;
    CString message;
};


