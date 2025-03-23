#include "pch.h"
#include "IOCPCoreWrapper.h"

DummyClientWrapper::ManagedIOCPCore::ManagedIOCPCore()
{
    _native = new IOCPCore();
}

DummyClientWrapper::ManagedIOCPCore::~ManagedIOCPCore()
{
    delete _native;
}

void DummyClientWrapper::ManagedIOCPCore::RegisterSocket(SOCKET socket)
{
    _native->RegisterSocket(socket);
}

bool DummyClientWrapper::ManagedIOCPCore::Dispatch(unsigned int time)
{
    return _native->Dispatch(time);
}
