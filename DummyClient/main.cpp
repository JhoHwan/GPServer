#include "pch.h"

#include <unordered_set>

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
		shared_ptr<Session> session = make_shared<Session>();
		session->CreateSocket();
		_sessions.insert(session);

		_connector->Connect(ip, port, session);
	}

private:
	shared_ptr<Connector> _connector;
	unordered_set<shared_ptr<Session>> _sessions;

};



int main()
{
	DummyClient client;

	client.Connect(L"127.0.0.1", 7777);


	while (true) {}
}