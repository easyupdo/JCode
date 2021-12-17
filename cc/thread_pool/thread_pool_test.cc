#include "thread_pool.h"

#include <chrono>

#include "update_work_unit.h"

int main(int argc, char** argv) {
  ThreadPool thread_pool(1);

  UpdateWorkUnit::Ptr work_ptr1 = std::make_shared<UpdateWorkUnit>("work1");
  UpdateWorkUnit::Ptr work_ptr2 = std::make_shared<UpdateWorkUnit>("work2");
  UpdateWorkUnit::Ptr work_ptr3 = std::make_shared<UpdateWorkUnit>("work3");
  size_t index = 0;
  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    switch (index) {
      case 0:
        thread_pool.SubmitWork(work_ptr1);
        index += 1;
        break;

      case 1:
        thread_pool.SubmitWork(work_ptr2);
        index += 1;
        break;

      case 2:
        thread_pool.SubmitWork(work_ptr3);
        index = 0;
        break;

      default:
        index = 0;
        break;
    }
  }

  return 0;
}