#include "pch.h"

#include <unordered_set>
#include "DummyClientPacketHandler.h"
#include "DummySession.h"

class DummyClient : public IOCPCore
{

public:
	DummyClient() : IOCPCore(), _connector(make_shared<Connector>())
	{
		for (int i = 0; i < 4; i++)
		{
			thread t([this]()
				{
					while (true)
					{
						Dispatch(1000);
					}
				});
			t.detach();
		}
	}

    void Connect(const wstring& ip, uint16 port)
	{
		shared_ptr<Session> session = make_shared<DummySession>();
		session->CreateSocket();
		_sessions.insert(session);
		RegisterSocket(session->GetSocket());

		_connector->Connect(ip, port, session);
	}

private:
	shared_ptr<Connector> _connector;
	unordered_set<shared_ptr<Session>> _sessions;

};



int main()
{
	DummyClientPacketHandler::Init();

	DummyClient client;
	
	
	client.Connect(L"127.0.0.1", 7777);


	while (true) {}
}