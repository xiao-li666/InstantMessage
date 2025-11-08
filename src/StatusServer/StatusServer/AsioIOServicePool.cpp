#include "AsioIOServicePool.h"

AsioIOServicePool::~AsioIOServicePool()
{
	Stop();
	std::cout << "AsioIOServicePool destroyed." << std::endl;
}

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	: _nextIOContext(0), _ioContext(size),_workGuards(size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		_workGuards[i] = std::make_unique<Work>(boost::asio::make_work_guard(_ioContext[i]));
	}
	for (std::size_t i = 0; i < size; ++i)
	{
		_threads.emplace_back([this, i]() {
			_ioContext[i].run();
			});
	}
}

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto& service = _ioContext[_nextIOContext++];
	if (_nextIOContext == _ioContext.size()) {
		_nextIOContext = 0;
	}
	return service;
}

void AsioIOServicePool::Stop()
{
	for (auto& ioService : _ioContext)
	{
		ioService.stop();
	}
	for (auto& workGuard : _workGuards)
	{
		workGuard->reset();
	}
	for (auto& thread : _threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}
