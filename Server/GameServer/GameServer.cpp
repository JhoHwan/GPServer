#include "pch.h"

#include "GameServer.h"
#include "BroadcastManager.h"
#include "World.h"

using Time = std::chrono::high_resolution_clock;

GameServer::GameServer(NetAddress address, SessionFactory sessionFactory)
	: IOCPServer(address, sessionFactory), _jobQueue(make_shared<DoubleJobQueue>())
{

}

void GameServer::InsertJob(shared_ptr<Job> job)
{
	_jobQueue->InsertJob(job);
}

// ExcuteJobQueue -> GameObjectUpdate -> Event -> Braodcast -> SwapQueue
void GameServer::GameLoop(std::chrono::milliseconds updateInterval)
{
	double deltaTime = 0;
	auto beforeTime = Time::now();

	while (true)
	{
		_jobQueue->SwapQueue();

		auto curTime = Time::now();
		std::chrono::duration<double> dif  = (curTime - beforeTime);
		deltaTime = dif.count();

		beforeTime = curTime;

		auto nextFrameTime = Time::now() + updateInterval;

		_jobQueue->ExecuteJob();

		World::Instance()->Update(deltaTime);

		::GGameObjectManager()->UpdateAll(deltaTime);

		BroadcastManager::Instance()->Broadcast(deltaTime);

		// Busy Waiting
		while (Time::now() < nextFrameTime)
		{
			std::this_thread::yield();
		}
	}
}
