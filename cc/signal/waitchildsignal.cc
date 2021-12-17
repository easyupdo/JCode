/**
 * @file waitchildsignal.cc
 * @author your name (you@domain.com)
 * @brief 测试主程kill子程后接受子程的信号防止子程变成僵尸进程
 * @version 0.1
 * @date 2021-12-14
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <string.h>

bool WaitChildSignal(std::chrono::nanoseconds waitTime) {
  sigset_t sigset;
  sigset_t old_sigset;
  struct timespec timeout = {0, 0};
  timeout.tv_nsec = static_cast<decltype(timeout.tv_nsec)>(waitTime.count());
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGCHLD);

  (void)sigprocmask(SIG_BLOCK, &sigset, &old_sigset);

  auto sigRet = sigtimedwait(&sigset, NULL, &timeout);
  std::cout << "sigtimedwait:sigRet" << sigRet << std::endl;
  if (sigRet == -1) {
    if (errno == EINVAL) {
      std::cout << "Invalid argument for sigtimedwait" << std::endl;
    } else {
      std::cout << "sigtimedwait false" << std::endl;
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {
  signal(SIGCHLD, [](int signum) {
    std::cout << "SIGCHLD:" << signum << std::endl;

    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
  });

  pid_t pid;
  pid = fork();
  if (pid == 0) {
    // while (1) {
      std::this_thread::sleep_for(std::chrono::seconds(5));
      std::cout << "child pid" << std::endl;

      std::string cmd = "/home/rosfoxy/Easyup/JCode/cc/signal/hello";

      char* argv[2];
      argv[0] = "--string=GOSB";
      argv[1] = NULL;

      char* const* childArgv = const_cast<char* const*>(argv);

      int ret = execv(cmd.c_str(), childArgv);
      std::cout<<"execv:"<<ret<<strerror(errno)<<std::endl;
    // }

    while(1){
        std::cout<<"child go"<<std::endl;
    }
  } else if (pid > 0) {
    std::cout << "father pid:" << pid << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    int signum = SIGKILL;
    std::cout<<"Send kill"<<std::endl;
    kill(pid, signum);
    // std::string cmd = "kill -9 " + std::to_string(signum);

    // system(cmd.c_str());
    while (1)
      ;
  } else {
    std::cout << "error" << std::endl;
  }

  return 0;
}
