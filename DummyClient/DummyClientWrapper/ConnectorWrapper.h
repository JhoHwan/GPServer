#pragma once
#include <msclr/marshal.h>

namespace DummyClientWrapper
{
	public ref class ManagedConnector
	{
	public:
		ManagedConnector();
		~ManagedConnector();

        void Connect(String^ ip, uint16 port, ManagedDummySession^ session)
        {
			pin_ptr<const wchar_t> pinnedIP = PtrToStringChars(ip);
			wstring convertIP(pinnedIP);
            (*_native)->Connect(convertIP, port, session->GetNativeSession());
        }
	private:
		shared_ptr<Connector>* _native;
	};
}