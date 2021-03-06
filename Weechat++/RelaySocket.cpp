// CRelaySocket.cpp : implementation file
//

#include "stdafx.h"
#include "RelaySocket.h"
#include "RelayConnection.h"

// CRelaySocket

CRelaySocket::CRelaySocket()
    : CAsyncSocket()
{
    m_pConn = nullptr;
}

CRelaySocket::~CRelaySocket()
{
}

void CRelaySocket::SetConnection(CRelayConnection *conn)
{
    m_pConn = conn;
}

void CRelaySocket::OnAccept(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnAccept(nErrorCode);
}

void CRelaySocket::OnClose(int nErrorCode)
{
    m_pConn->OnClose(nErrorCode);

    CAsyncSocket::OnClose(nErrorCode);
}

void CRelaySocket::OnConnect(int nErrorCode)
{
    m_pConn->OnConnect(nErrorCode);

    CAsyncSocket::OnConnect(nErrorCode);
}

void CRelaySocket::OnOutOfBandData(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CRelaySocket::OnReceive(int nErrorCode)
{
    m_pConn->OnReceive(nErrorCode);

    CAsyncSocket::OnReceive(nErrorCode);
}

void CRelaySocket::OnSend(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnSend(nErrorCode);
}

// CRelaySocket member functions
