#pragma once

class IOCPServer;
class AcceptEvent;

class Listener : public IOCPObject
{
public:
    // ������ �� �Ҹ���
    Listener(unsigned int maxAcceptNum = 100);
    ~Listener();

    // Accept ����
    bool StartAccept(std::shared_ptr<IOCPServer> server);
    void RegisterAccept(AcceptEvent* acceptEvent);
    void ProcessAccept(AcceptEvent* acceptEvent);

    void Dispatch(IOCPEvent* iocpEvent, int32 numOfBytes) override;

    // Getter
    inline const SOCKET& GetSocket() const { return _socket; }

private:
    const unsigned int MAX_ACCEPT_NUM;
    std::shared_ptr<IOCPServer> _server;
    std::vector<AcceptEvent> _acceptEvents; 
    SOCKET _socket = {};


};