#pragma once

using namespace System;

class DummySession;

namespace DummyClientWrapper 
{
	public ref class ManagedDummySession abstract
	{
	public:
		ManagedDummySession();
		~ManagedDummySession();
		!ManagedDummySession();

		virtual void OnConnected() abstract;
		virtual void OnDisConnected() abstract;
		virtual void OnRecv(uint32 sentBytes) abstract;
		virtual void OnSend(uint32 sentBytes) abstract;

		void CreateSocket();

        void Send(cli::array<Byte>^ buffer);
		void Disconnect();

		SOCKET GetSocket();

		shared_ptr<Session> GetNativeSession();

	private:

		std::shared_ptr<DummySession>* _native;
	};
}
