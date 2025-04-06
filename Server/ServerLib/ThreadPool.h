#pragma once

class ThreadPool
{
public:
	ThreadPool(uint32 threadCount)
	{
		_running.store(true);

		for (uint32 i = 0; i < threadCount; i++)
		{
			_workers.emplace_back([this]() { WorkerLoop(); });
		}
	}

	virtual ~ThreadPool()
	{
		_running = false;
		_cv.notify_all();

		for (auto& t : _workers)
		{
			if (t.joinable()) t.join();
		}
	}

	void Enqueue(std::function<void()> task)
	{
		_queue.enqueue(std::move(task));

		_cv.notify_one();
	}

private:
	void WorkerLoop()
	{
		const uint32 maxTryCount = 2000;
		uint32 tryCount = 0;

		while (_running.load())
		{
			std::function<void()> task;
			if (_queue.try_dequeue(task))
			{
				task();
			}
			else
			{
				tryCount++;
				
				if (tryCount > maxTryCount)
				{
					std::unique_lock<std::mutex> lock(_cvMutex);
					_cv.wait(lock, [this]() 
						{ return _queue.size_approx() != 0 || !_running.load(); });
					tryCount = 0;
				}
				else
				{
					std::this_thread::yield();
				}
			}
		}
	}

private:
	std::vector<std::thread> _workers;
	ConcurrentQueue<std::function<void()>> _queue;

	std::mutex _cvMutex;
	std::condition_variable _cv;

	std::atomic<bool> _running;
};