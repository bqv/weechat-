#pragma once

#include "stdafx.h"

class CBufferView : public CDockablePane
{
	DECLARE_DYNAMIC(CBufferView)

public:
	CBufferView();
	virtual ~CBufferView();

protected:
	DECLARE_MESSAGE_MAP()
};


