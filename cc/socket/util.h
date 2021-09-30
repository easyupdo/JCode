#ifndef _UTIL_H
#define _UTIL_H
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <future>
#include <functional>
#include "log.hpp"
#include "header.h"
void CharOut(void * s,int32_t pos, int32_t size,std::string flag);

void HexOut(void * s,int32_t pos,int32_t size,std::string flag);

void StringOut(void * s,int32_t pos, int32_t size,std::string flag);




class Util{
    public:
    Util(){}

    int32_t Serialize(const void * src,int32_t byte_size);
    int32_t Serialize(std::string src,int32_t byte_size);
    int32_t Serialize(Header src,int32_t byte_size);

    int32_t UnserializeHeader(void*src);

    void ClearBuffer(){
        buffer_.clear();
    }

    std::vector<unsigned char> get_buffer(){return buffer_;}

    protected:
    private:
    std::vector<unsigned char> buffer_;

};

class Parse {
    public:
    Parse(){}
    ~Parse(){}

};



class Timer
{
public:
	Timer(): expired_(true), try_to_expire_(false)
	{}

	Timer(const Timer& timer)
	{
		expired_ = timer.expired_.load();
		try_to_expire_ = timer.try_to_expire_.load();
	}

	~Timer()
	{
		stop();
	}

	void start(int interval, std::function<void()> task)
	{
		// is started, do not start again
		if (expired_ == false)
			return;

		// start async timer, launch thread and wait in that thread
		expired_ = false;
		std::thread([this, interval, task]() {
			while (!try_to_expire_)
			{
				// sleep every interval and do the task again and again until times up
				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				task();
			}

			{
				// timer be stopped, update the condition variable expired and wake main thread
				std::lock_guard<std::mutex> locker(mutex_);
				expired_ = true;
				expired_cond_.notify_one();
			}
		}).detach();
	}

	void startOnce(int delay, std::function<void()> task)
	{
		std::thread([delay, task]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			task();
		}).detach();
	}

	void stop()
	{
		// do not stop again
		if (expired_)
			return;

		if (try_to_expire_)
			return;

		// wait until timer 
		try_to_expire_ = true; // change this bool value to make timer while loop stop
		{
			std::unique_lock<std::mutex> locker(mutex_);
			expired_cond_.wait(locker, [this] {return expired_ == true; });

			// reset the timer
			if (expired_ == true)
				try_to_expire_ = false;
		}
	}

private:
	std::atomic<bool> expired_; // timer stopped status
	std::atomic<bool> try_to_expire_; // timer is in stop process
	std::mutex mutex_;
	std::condition_variable expired_cond_;
};




#endif //_UTIL_H