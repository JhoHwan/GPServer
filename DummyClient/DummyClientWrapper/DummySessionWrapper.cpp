#include "pch.h"

#include "DummySession.h"

using namespace DummyClientWrapper;

DummyClientWrapper::ManagedDummySession::ManagedDummySession()
{
    _native = new std::shared_ptr<DummySession>(std::make_shared<DummySession>(gcroot<ManagedDummySession^>(this)));
}

DummyClientWrapper::ManagedDummySession::~ManagedDummySession()
{
    this->!ManagedDummySession();
}

DummyClientWrapper::ManagedDummySession::!ManagedDummySession()
{
    if (_native != nullptr)
    {
        (*_native).reset();
        delete _native;
        _native = nullptr;
    }
}

void DummyClientWrapper::ManagedDummySession::CreateSocket()
{
    (*_native)->CreateSocket();
}

void DummyClientWrapper::ManagedDummySession::Send(cli::array<Byte>^ buffer)
{
    pin_ptr<Byte> pByteArray = &buffer[0];
    char* nativeCharArray = reinterpret_cast<char*>(pByteArray);

    auto sendBuffer = make_shared<SendBuffer>(buffer->Length);
    sendBuffer->CopyData(nativeCharArray, buffer->Length);

    (*_native)->Send(sendBuffer);
}

void DummyClientWrapper::ManagedDummySession::Disconnect()
{
    (*_native)->Disconnect();
}

SOCKET DummyClientWrapper::ManagedDummySession::GetSocket()
{
    return (*_native)->GetSocket();
}

shared_ptr<Session> DummyClientWrapper::ManagedDummySession::GetNativeSession()
{
    return (*_native);
}