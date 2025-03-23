#pragma once

#include "NetAddress.h"
#include "IOCPEvent.h"
#include "RecvBuffer.h"

class IOCPServer;
class SendBuffer;
class PacketHandler;

class Session : public IOCPObject
{
    enum { MAX_SEND_SIZE = 512 };
public:
    // ������ �� �Ҹ���
    Session();
    virtual ~Session();

    void CreateSocket();

    virtual void Dispatch(class IOCPEvent* iocpEvent, int32 numOfBytes = 0) override;

    // ���� ����
    void Connect();
    void ProcessConnect();

    void Disconnect();
    void RegisterDisconnect();
    void ProcessDisconnect();

    // TODO : �ӽ÷� ���� ���, SendBuffer ���� ���� ����
    // ������ ���� ����
    void Send(shared_ptr<SendBuffer> sendBuffer);
    void RegisterSend();
    void ProcessSend(uint32 sentBytes);

    // ������ ���� ����
    void RegisterRecv();
    void ProcessRecv(uint32 recvBytes);

    // �̺�Ʈ �ڵ鷯
    virtual void OnConnected();
    virtual void OnDisconnected();
    virtual void OnSend(uint32 sentBytes);
    virtual void OnRecv(BYTE* buffer, int32 len);

    // Setter
    inline void SetServer(std::shared_ptr<IOCPServer> server) { _server = server; }
    inline void SetAddress(const NetAddress& address) { _address = address; }

    // Getteter 
    inline SOCKET GetSocket() { return _socket; }
    inline RecvBuffer& GetRecvBuffer() { return _recvBuffer; }
    inline const NetAddress& GetAddress() const { return _address; }
    inline shared_ptr<Session> GetSharedPtr() { return static_pointer_cast<Session>(shared_from_this()); }
    inline shared_ptr<IOCPServer> GetServer() { return _server; }

protected:
    atomic<bool> _isConnect;
    SOCKET _socket;
    std::shared_ptr<IOCPServer> _server;

    NetAddress _address;

    RecvBuffer _recvBuffer;
    queue<shared_ptr<SendBuffer>> _sendQueue;

    mutex _sendLock;
    atomic<bool> _sendRegistered;
    //TODO : Lock-Free Queue �����غ���
//IOCP Event
protected:
    RecvEvent _recvEvent;
    SendEvent _sendEvent;
    DisconnectEvent _disConnectEvent;
};

