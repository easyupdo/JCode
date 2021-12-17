// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

#include "thread_pool.h"

#include <exception>
#include <iostream>


ThreadPool::ThreadPool(const unsigned capacity)
    // : log_(ara::log::CreateLogger("THRX", "ThreadPool logging context"))
{
    threads_.reserve(capacity);
    for (unsigned i = 0; i < capacity; ++i) {
        threads_.emplace_back(&ThreadPool::Worker, this);
        pthread_setname_np(threads_.back().native_handle(), "WorkerThread");
    }
}

ThreadPool::~ThreadPool()
{
    for (std::thread& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::SubmitWork(WorkUnit::Ptr work_unit)
{
    std::lock_guard<std::mutex> lock(work_queue_mutex_);
    work_queue_.emplace_back(work_unit);
    work_queue_condvar_.notify_one();
}

void ThreadPool::Worker()
{
    while (running_) {
        WorkOne();
    }
}

void ThreadPool::WorkOne()
{
    // Attempt to get a unit of work
    WorkUnit::Ptr work_unit;
    {
        std::unique_lock<std::mutex> lock(work_queue_mutex_);
        while (running_ && work_queue_.empty()) {
            work_queue_condvar_.wait(lock);
        }
        if (running_) {
            work_unit = work_queue_.front();
            work_queue_.pop_front();
        }
    }

    // If we got work, execute it.
    if (work_unit) {
        try {
            work_unit->Run();
        } catch (std::exception& e) {
            std::cout << "Exception occurred while processing unit of work " << ": " << e.what();
        } catch (...) {
            std::cout << "Unknown Error occurred while processing unit of work ";
        }
    }
}

