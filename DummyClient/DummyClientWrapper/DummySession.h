#pragma once
#include <vcclr.h>

using namespace DummyClientWrapper;

public class DummySession : public Session
{
public:
	DummySession(gcroot<ManagedDummySession^> obj) : _managedObject(obj)
	{

	}

	virtual ~DummySession() override
	{
	}

	virtual void OnConnected() override
	{
		_managedObject->OnConnected();
	}

	virtual void OnDisconnected() override
	{
		_managedObject->OnDisConnected();
	}

	virtual void OnSend(uint32 sentBytes) override
	{
		_managedObject->OnSend(sentBytes);
	}

	virtual void OnRecv(BYTE* buffer, int32 len) override
	{
		_managedObject->OnRecv(len);
	}

private:
	gcroot<ManagedDummySession^> _managedObject;
};
