#pragma once

class GameServer : public IOCPServer
{
public:
	GameServer(NetAddress address, SessionFactory sessionFactory);

	void InsertJob(shared_ptr<Job> job);

	void GameLoop(std::chrono::milliseconds frameTime);

private:
	shared_ptr<DoubleJobQueue> _jobQueue;
};

