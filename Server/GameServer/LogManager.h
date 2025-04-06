#pragma once

#include "Singleton.h"

class LogManager;

extern LogManager Log;

class LogManager
{
public:
    LogManager() : _pool(ThreadPool(1)) {}
	~LogManager() = default;

	void Log(const std::string& log)
	{
		_pool.Enqueue([log = log]()
			{
				cout << log << endl;
			});
	}

    template<typename T>
    LogManager& operator<<(const T& value)
    {
        _oss << value;
        return *this;
    }

    LogManager& operator<<(std::ostream& (*manip)(std::ostream&))
    {
        if (manip == static_cast<std::ostream & (*)(std::ostream&)>(std::endl))
        {
            std::string log = _oss.str();
            _oss.str("");
            _oss.clear();

            _pool.Enqueue([log = std::move(log)]()
                {
                    cout << log << endl;
                });
        }
        else
        {
            manip(_oss);
        }

        return *this;
    }

private:
	ThreadPool _pool;
    std::ostringstream _oss;
};

