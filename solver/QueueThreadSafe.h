#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>


template <typename T>
class QueueThreadSafe
{
public:
	QueueThreadSafe();
	~QueueThreadSafe();

	bool tryPop(T& out);
	bool waitPop(T& out);
	void push(T value);
	bool empty()const;
	void clear();
	void invalidate();
	bool isValid() const;

private:
	std::atomic_bool _valid = true;
	mutable std::mutex _mutex;
	std::queue<T> _queue;
	std::condition_variable _condition;
};
template <typename T>
QueueThreadSafe<T>::QueueThreadSafe() {}

template <typename T>
QueueThreadSafe<T>::~QueueThreadSafe<T>() { invalidate(); }

/*
Try  to get first value in queue
*/
template <typename T>
bool QueueThreadSafe<T>::tryPop(T& out)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_queue.empty() || !_valid)
		return false;
	out = std::move(_queue.front());
	_queue.pop();
	return true;
}

/*
Get first value in queue
Waits until possible,
all threads are blocked at the condition.wait and one thread at the time 
*/
template <typename T> 
bool QueueThreadSafe<T>::waitPop(T& out)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_condition.wait(lock, [this]() {return !_queue.empty() || !_valid; });
	if (!_valid)
		return false;
	out = std::move(_queue.front());
	_queue.pop();
	return true;
}

template <typename T> 
void QueueThreadSafe<T>::push(T value)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_queue.push(std::move(value));
	_condition.notify_one();
}

template <typename T> 
bool QueueThreadSafe<T>::empty()const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _queue.empty();
}

template <typename T> 
void QueueThreadSafe<T>::invalidate()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_valid = false;
	_condition.notify_all();
}

template <typename T> 
bool QueueThreadSafe<T>::isValid() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _valid;
}

template <typename T> 
void QueueThreadSafe<T>::clear()
{
	std::lock_guard<std::mutex> lock(_mutex);
	while (!_queue.empty)
		_queue.pop();
	_condition.notify_all();
}