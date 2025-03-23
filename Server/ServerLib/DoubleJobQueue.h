#pragma once

class DoubleJobQueue
{
public:
	DoubleJobQueue();
	~DoubleJobQueue();

	void InsertJob(shared_ptr<Job> job);

	void ExecuteJob();

	void SwapQueue();

    // 여기서 락 잡는 시간 측정!
	long long SwapQueueWithTiming();

private:
	std::mutex _lock;

	std::queue<shared_ptr<Job>>* _insertJobQueue;
	std::queue<shared_ptr<Job>>* _executeJobQueue;

};
