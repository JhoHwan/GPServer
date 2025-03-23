#include "pch.h"

#include "GameServer.h"

using Time = std::chrono::high_resolution_clock;

GameServer::GameServer(NetAddress address, SessionFactory sessionFactory)
	: IOCPServer(address, sessionFactory), _jobQueue(make_shared<DoubleJobQueue>())
{

}

void GameServer::InsertJob(shared_ptr<Job> job)
{
	_jobQueue->InsertJob(job);
}

// ExcuteJobQueue -> GameObjectUpdate -> HandleEvent -> Braodcast
void GameServer::GameLoop(std::chrono::milliseconds frameTime)
{
	while (true)
	{
		auto nextFrameTime = Time::now() + 33ms;

		_jobQueue->ExecuteJob();

		::GGameObjectManager()->UpdateAll();

		// Busy Waiting
		while (Time::now() < nextFrameTime)
		{
			std::this_thread::yield();
		}

		_jobQueue->SwapQueue();
	}
}
