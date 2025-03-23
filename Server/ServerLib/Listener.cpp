#include "pch.h"
#include "Listener.h"

#include "IOCPServer.h"
#include "IOCPEvent.h"
#include "NetAddress.h"
#include "Session.h"
#include "SocketUtil.h"

Listener::Listener(unsigned int maxAcceptNum) : MAX_ACCEPT_NUM(maxAcceptNum), _acceptEvents(maxAcceptNum, AcceptEvent())
{

}

Listener::~Listener()
{
	cout << "Release Listener" << endl;
}

// ��Ĺ �ʱ�ȭ �� �񵿱� Accept�� ����Ѵ�.
bool Listener::StartAccept(shared_ptr<IOCPServer> server)
{
	cout << "Start Listener" << endl;

	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), OUT & wsaData))
	{
		cout << "WSAStartup Error" << endl;
		return false;
	}

	_server = server;

	_socket = SocketUtil::CreateSocket();
	if (_socket == INVALID_SOCKET)
	{
		cout << "WSASocket Error : " << WSAGetLastError() << endl;
		return false;
	}

	if (!server->GetIOCPCore().RegisterSocket(_socket))
	{
		return false;
	}

	// ���� �ɼ� SO_REUSEADDR ���� (�ּ� ���� ���)
	if (SocketUtil::SetReuseAddr(_socket) == false)
	{
		cout << "SetReuseAddr Error : " << WSAGetLastError() << endl;
		return false;
	}

	if (SocketUtil::SetLinger(_socket, 0, 0) == false)
		return false;

	// ���� ���ε�
	if (SocketUtil::Bind(_socket, _server->GetAddress()) == false)
	{
		cout << "Bind Error : " << WSAGetLastError() << endl;
		return false;
	}

	// ������ Ŭ���̾�Ʈ ��û ���� ��� ���·� ����
	if (SocketUtil::Listen(_socket) == false)
	{
		cout << "Listen Error : " << WSAGetLastError() << endl;
		return false;
	}

	for (int i = 0; i < MAX_ACCEPT_NUM; i++)
	{
		RegisterAccept(&_acceptEvents[i]);
	}

	cout << "Start Listener Finish" << endl;
	return true;
}

void Listener::RegisterAccept(AcceptEvent* acceptEvent)
{ 
	// ���ο� Session ����
	shared_ptr<Session> session = _server->CreateSession();

	// acceptEvent �ʱ�ȭ �� Session ����
	acceptEvent->Init();
	acceptEvent->owner = shared_from_this();
	acceptEvent->session = session;
	
	DWORD bytesReceived = 0;
	if (false == ::AcceptEx(_socket, session->GetSocket(), session->GetRecvBuffer().WritePos(), 0,
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, OUT & bytesReceived, reinterpret_cast<LPOVERLAPPED>(acceptEvent)))
	{
		auto errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			//TODO : LOG
			acceptEvent->session = nullptr;
			cout << errCode << endl;
			RegisterAccept(acceptEvent);
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	// Accept�� ���Ͽ� ������ ������ �ɼ��� ����
	if (SocketUtil::SetAcceptSockOption(acceptEvent->session->GetSocket(), _socket) == false)
	{
		cout << "SetAcceptSockOption Error : " << WSAGetLastError() << endl;
		RegisterAccept(acceptEvent);
		return;
	}

	NetAddress address; 
	if (false == SocketUtil::GetNetAddressBySocket(acceptEvent->session->GetSocket(), address))
	{
		cout << "GetNetAddressBySocket Error : " << WSAGetLastError() << endl;
		RegisterAccept(acceptEvent);
		return;
	}

	acceptEvent->session->SetAddress(address);

	_server->AddSession(acceptEvent->session);
	acceptEvent->session->ProcessConnect();
	acceptEvent->session = nullptr;

	// ���� ���� ��û�� ó���ϵ��� Accept ���
	RegisterAccept(acceptEvent);
}

void Listener::Dispatch(IOCPEvent* iocpEvent, int32 numOfBytes)
{
	if (iocpEvent->GetEventType() != EventType::Accept)
	{
		return;
	}

	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}
