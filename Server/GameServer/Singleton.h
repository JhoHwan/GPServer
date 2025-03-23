#pragma once

template<typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

private:
	struct Deleter
	{
		void operator()(T* inst)
		{
			delete inst;
		}
	};

private:
	static std::unique_ptr<T, Deleter> _pInst;
	static std::once_flag _flag;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	static std::unique_ptr<T, Deleter>& Instance()
	{
		std::call_once(_flag, []()
			{
				Singleton<T>::_pInst.reset(new T);

				char name[256] = { 0 };
				sprintf_s(name, "%s instantiated\n", typeid(T).name());
			});

		return _pInst;
	}
};

template<typename T>
std::unique_ptr<T, typename Singleton<T>::Deleter>
Singleton<T>::_pInst = std::unique_ptr<T, typename Singleton<T>::Deleter>(nullptr, typename Singleton<T>::Deleter());

template<typename T>
std::once_flag Singleton<T>::_flag;