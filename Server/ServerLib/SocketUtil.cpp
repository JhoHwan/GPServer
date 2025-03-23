#include "pch.h"
#include "SocketUtil.h"
#include "NetAddress.h"

LPFN_DISCONNECTEX SocketUtil::DisconnectEx = nullptr;
LPFN_CONNECTEX SocketUtil::ConnectEx = nullptr;

SOCKET SocketUtil::CreateSocket() 
{
    // Overlapped I/O�� �����ϴ� ���� ����
    return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
}

bool SocketUtil::Bind(SOCKET socket, const NetAddress& address) 
{
    // NetAddress ��ü���� sockaddr_in ����ü ��������
    const sockaddr_in& sockAddr = address.GetAddress();

    // ������ Ư�� IP�� ��Ʈ�� ���ε�
    return ::bind(socket, reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockAddr)) != SOCKET_ERROR;
}

bool SocketUtil::BindAnyAddress(SOCKET socket, uint16 port)
{
    if (socket == INVALID_SOCKET)
    {
        return false;
    }

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    addr.sin_port = ::htons(port);

    return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&addr), sizeof(addr));
}

bool SocketUtil::Listen(SOCKET socket, int backlog) 
{
    // ������ Ŭ���̾�Ʈ ���� ��û ���� ��� ���·� ����
    return ::listen(socket, backlog) != SOCKET_ERROR;
}

bool SocketUtil::SetReuseAddr(SOCKET socket) 
{
    int optval = 1; // �ɼ� Ȱ��ȭ ��

    // setsockopt�� ����Ͽ� SO_REUSEADDR �ɼ� ���� (�ּ� ���� ���)
    return ::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optval), sizeof(optval)) == 0;
}

bool SocketUtil::SetNoDelay(SOCKET socket) 
{
    int optval = 1; // �ɼ� Ȱ��ȭ ��

    // setsockopt�� ����Ͽ� TCP_NODELAY ���� (Nagle �˰��� ��Ȱ��ȭ)
    return ::setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&optval), sizeof(optval)) == 0;
}

bool SocketUtil::SetAcceptSockOption(SOCKET acceptedSocket, SOCKET listenSocket) 
{
    // Accept�� ������ listen ������ �Ӽ��� ��ӹ޵��� SO_UPDATE_ACCEPT_CONTEXT ����
    return ::setsockopt(acceptedSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<const char*>(&listenSocket), sizeof(listenSocket)) == 0;
}

bool SocketUtil::GetNetAddressBySocket(SOCKET socket, NetAddress& netAddress)
{
    SOCKADDR_IN sockAddress;
    int32 sizoOfSockAddr = sizeof(sockAddress);
    if (SOCKET_ERROR == ::getpeername(socket, OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizoOfSockAddr))
    {
        return false;
    }

    netAddress = NetAddress(sockAddress);
    return true;
}

bool SocketUtil::SetLinger(SOCKET socket, uint16 onoff, uint16 linger)
{
    LINGER option;
    option.l_onoff = onoff;
    option.l_linger = linger;
    return SOCKET_ERROR != setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*) & option, sizeof(option));
}

void SocketUtil::CloseSocket(SOCKET socket) {
    // ������ ��ȿ�ϸ� �ݱ�
    if (socket != INVALID_SOCKET) ::closesocket(socket);
    socket = INVALID_SOCKET;
}

LPFN_DISCONNECTEX SocketUtil::GetDisconnectEx()
{
    if (DisconnectEx == nullptr) LoadDisconnectEx();
    return DisconnectEx;
}

LPFN_CONNECTEX SocketUtil::GetConnectEx()
{
    if (ConnectEx == nullptr) LoadConnectEx();
    return ConnectEx;
}

void SocketUtil::LoadDisconnectEx()
{
    SOCKET socket = SocketUtil::CreateSocket();
    DWORD bytesReturned = 0;
    GUID guidDisconnectEx = WSAID_DISCONNECTEX;
    if (SOCKET_ERROR == ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDisconnectEx, sizeof(guidDisconnectEx), &DisconnectEx, sizeof(DisconnectEx), &bytesReturned, nullptr, nullptr))
    {
        cout << "LoadDisconnectEx Error" << WSAGetLastError() << endl;
    }

    SocketUtil::CloseSocket(socket);
}

void SocketUtil::LoadConnectEx()
{
    SOCKET socket = SocketUtil::CreateSocket();
    DWORD bytesReturned = 0;
    GUID guidConnectEx = WSAID_CONNECTEX;
    if (SOCKET_ERROR == ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidConnectEx, sizeof(guidConnectEx), &ConnectEx, sizeof(ConnectEx), &bytesReturned, nullptr, nullptr))
    {
        cout << "LoadConnectEx Error" << WSAGetLastError() << endl;
    }

    SocketUtil::CloseSocket(socket);
}

