#pragma once

using namespace System;

namespace DummyClientWrapper 
{
	public ref class ManagedIOCPCore
	{
	public:
		ManagedIOCPCore();
		~ManagedIOCPCore();

		void RegisterSocket(SOCKET socket);

		bool Dispatch(unsigned int time);

	private:
		IOCPCore* _native;
	};
}