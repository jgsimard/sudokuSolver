#pragma once

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#include "QueueThreadSafe.h"

/*
ThreadPool
private:
	-IThreadTask
	-ThreadTask
public:
	-TaskFuture
*/

//Declaration
class ThreadPool
{
private:
	class IThreadTask
	{
	public:
		IThreadTask() = default;
		virtual ~IThreadTask() = default;
		IThreadTask(const IThreadTask& rhs) = delete;
		IThreadTask& operator=(const IThreadTask& rhs) = delete;
		IThreadTask(IThreadTask&& other) = default;
		IThreadTask& operator=(IThreadTask&& other) = default;
		virtual void execute() = 0;
	};

	template <typename Func>
	class ThreadTask : public IThreadTask
	{
	public:
		ThreadTask(Func&& func);
		~ThreadTask() override = default;
		ThreadTask(const ThreadTask& rhs) = delete;
		ThreadTask& operator=(const ThreadTask& rhs) = delete;
		ThreadTask(ThreadTask&& other) = default;
		ThreadTask& operator=(ThreadTask&& other) = default;
		void execute() override;
	private:
		Func _func;
	};
public:
	template <typename T>
	class TaskFuture
	{
	public:
		TaskFuture(std::future<T>&& future);
		~TaskFuture();
		TaskFuture(const TaskFuture& rhs) = delete;
		TaskFuture& operator=(const TaskFuture& rhs) = delete;
		TaskFuture(TaskFuture&& other) = default;
		TaskFuture& operator=(TaskFuture&& other) = default;
		auto get();
	private:
		std::future<T> _future;


	};
	ThreadPool();
	~ThreadPool();
	explicit ThreadPool(const std::uint32_t numThreads);
	ThreadPool(const ThreadPool& rhs) = delete; // not copiable
	ThreadPool& operator=(const ThreadPool& rhs) = delete; // not assignable

	template <typename Func, typename... Args>
	auto submit(Func&& func, Args&&... args);



private:
	void worker();
	void destroy();

	std::atomic_bool _done;
	QueueThreadSafe <std::unique_ptr<IThreadTask>> _work_queue;
	std::vector<std::thread> _threads;

};
//Helper function
ThreadPool& get_ThreadPool()
{
	static ThreadPool pool;
	return pool;
}

template <typename Func, typename... Args>
inline auto submit_job(Func&& func, Args... args)
{
	return get_ThreadPool().submit(std::foward<Func>(func), std::forward<Args>(args)...);
}

//Implementation

template <typename Func> ThreadPool::ThreadTask<Func>::ThreadTask(Func&& func) : _func(std::move(func)) {}
template <typename Func> void ThreadPool::ThreadTask<Func>::execute() { _func(); }

template <typename T> ThreadPool::TaskFuture<T>::TaskFuture(std::future<T>&& future) : _future(std::move(future)) {}
template <typename T> ThreadPool::TaskFuture<T>::~TaskFuture() { if (_future.valid()) _future.get(); }
template <typename T> auto ThreadPool::TaskFuture<T>::get() { return _future.get(); }

ThreadPool::ThreadPool(const std::uint32_t numThreads) : _done(false), _work_queue(), _threads()
{
	try
	{
		for (std::uint32_t i = 0u; i < numThreads; ++i)
			_threads.emplace_back(&ThreadPool::worker, this);
	}
	catch (...)
	{
		destroy();
		throw;
	}
}

ThreadPool::ThreadPool() : ThreadPool(std::max(std::thread::hardware_concurrency(), 2u) - 1u) {}
ThreadPool::~ThreadPool() { destroy(); }

template <typename Func, typename... Args>
auto ThreadPool::submit(Func&& func, Args&&... args)
{
	auto boundTask = std::bind(std::foward<Func>(func), std::foward<Args>(args)...);
	using ResultType = std::result_of_t<decltype(boundTask)()>;
	using PackagedTask = std::packaged_task<ResultType()>;
	using TaskType = ThreadTask<PackagedTask>;

	PackagedTask task(std::move(boundTask));
	TaskFuture<ResultType> result(task.get_future());
	_work_queue.push(std::make_unique<TaskType>(std::move(task)));
	return result;
}

void ThreadPool::worker()
{
	while (!_done) {
		std::unique_ptr<IThreadTask> pTask(nullptr);
		if (_work_queue.waitPop(pTask))
			pTask->execute();
	}
}

void ThreadPool::destroy()
{
	_done = true;
	_work_queue.invalidate();
	for (auto& thread : _threads)
		if (thread.joinable())
			thread.join();
}