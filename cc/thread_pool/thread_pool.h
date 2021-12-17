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

#ifndef SOURCE_COMMON_THREAD_POOL_H_
#define SOURCE_COMMON_THREAD_POOL_H_

#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

#include <vector>
#include "work_unit.h"


/**
 * \brief Implements a thread pool with a given capacity.
 */
class ThreadPool
{
public:
    /**
     * \brief Builds a new thread pool and starts the worker threads.
     *
     * \param capacity The number of worker threads to start.
     */
    explicit ThreadPool(const unsigned capacity);

    virtual ~ThreadPool();

    /**
     * \brief Submit a WorkUnit to the Thread Pool.
     */
    virtual void SubmitWork(WorkUnit::Ptr work_unit);

    /**
     * \brief Signal all worker threads to exit.
     *
     * Worker threads will exit once they complete their current work unit.
     */
    void Stop()
    {
        running_ = false;
        std::unique_lock<std::mutex> lock(work_queue_mutex_);
        work_queue_condvar_.notify_all();
    }

    bool IsEmpty() const
    {
        return work_queue_.empty();
    }

protected:
    /**
     * \brief Implementation of the Worker Thread.
     *
     * Calls WorkOne as long as running_ == true.
     */
    void Worker();

    /**
     * \brief Execution of a single work unit.
     *
     * Get a WorkUnit from the work_queue_ and calls WorkUnit#Run() on it.
     * If no work is available, blocks on work_queue_mutex_ and waits for a notification on work_queue_condvar_.
     */
    virtual void WorkOne();

    /**
     * \brief The worker threads.
     */
    std::vector<std::thread> threads_;

    /**
     * \brief Mutex to protect concurrent access to the work queue.
     */
    std::mutex work_queue_mutex_;

    /**
     * \brief Condition Variable to protect concurrent access to the work queue.
     */
    std::condition_variable work_queue_condvar_;

    /**
     * \brief The work queue.
     */
    std::deque<WorkUnit::Ptr> work_queue_;

    /**
     * \brief Flag to signal threads whether they should terminate.
     */
    std::atomic_bool running_{true};

    /*
     * \brief logging context instance
     */
    // ara::log::Logger& log_;
};

#endif /* SOURCE_COMMON_THREAD_POOL_H_ */
