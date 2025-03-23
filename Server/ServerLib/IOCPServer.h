#pragma once
#include "NetAddress.h"
#include "Listener.h"
#include "Session.h"

class PacketHandler;
class IOCPCore;

using SessionFactory = function<shared_ptr<Session>(void)>;

class IOCPServer : public std::enable_shared_from_this<IOCPServer>
{
public:
    // ������ �� �Ҹ���
    IOCPServer() = delete;
    IOCPServer(NetAddress address, SessionFactory sessionFactory);
    ~IOCPServer();

    shared_ptr<Session> CreateSession();

    virtual void BroadCast(shared_ptr<SendBuffer> sendBuffer);

    // ���� ����
    bool Start();
    bool Stop();

    // ���� ����
    void AddSession(std::shared_ptr<Session> session);
    void DeleteSession(std::shared_ptr<Session> session);

    // �̺�Ʈ ����ó
    void DispatchIocpEvent(uint16);
    void DispatchJob(uint16);
    void Dispatch(uint16 iocpDispatchTime);

    // Getter
    inline const NetAddress& GetAddress() const { return _address; }
    inline IOCPCore& GetIOCPCore() { return _iocpCore; }

protected:
	bool _isRunning = false;

    IOCPCore _iocpCore;

    NetAddress _address;

    shared_ptr<Listener> _listener;

    set<std::shared_ptr<Session>> _sessions;
    SessionFactory _sessionFactory;

	vector<std::thread> _iocpThreads;
// Mutex
protected:
    mutex _lock;
};
