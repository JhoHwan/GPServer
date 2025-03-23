#include "pch.h"
#include "IOCPCore.h"

IOCPCore::IOCPCore()
{
    _iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (_iocpHandle == INVALID_HANDLE_VALUE)
    {
        cout << "CreateIoCompletionPort Error" << endl;
    }
}

IOCPCore::~IOCPCore()
{
    ::CloseHandle(_iocpHandle);
}

bool IOCPCore::Register(HANDLE handle)
{
    // IOCP�� �ڵ� ���
    const unsigned int threadNum = std::thread::hardware_concurrency() * 2; //������Ǯ ũ�� ����

    if (::CreateIoCompletionPort(handle, _iocpHandle, 0, threadNum) == nullptr)
    {
        cout << "Register Error: " << GetLastError() << endl;
        return false;
    }

    return true;
}

bool IOCPCore::RegisterSocket(SOCKET socket)
{
    // ������ IOCP�� ���
    return Register(reinterpret_cast<HANDLE>(socket));
}

bool IOCPCore::Dispatch(uint32 time)
{
    DWORD lpNumberOfBytes;
    IOCPEvent* iocpEvent = nullptr;
    ULONG_PTR key = 0;

    if (::GetQueuedCompletionStatus(_iocpHandle, &lpNumberOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), static_cast<DWORD>(time)))
    {
        shared_ptr<IOCPObject> iocpObject = iocpEvent->owner;
        iocpObject->Dispatch(iocpEvent, lpNumberOfBytes);
    }
    else
    {
        if (GetLastError() == WAIT_TIMEOUT) return false;

        shared_ptr<IOCPObject> iocpObject = iocpEvent->owner;
        iocpObject->Dispatch(iocpEvent, static_cast<uint32>(lpNumberOfBytes));
    }
}

