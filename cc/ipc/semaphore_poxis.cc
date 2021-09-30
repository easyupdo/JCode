#include <iostream>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// poxis
#include <sys/mman.h>
#include <semaphore.h>

// /* Semaphore control operation.  */
// extern int semctl (int __semid, int __semnum, int __cmd, ...) __THROW;

// /* Get semaphore.  */
// extern int semget (key_t __key, int __nsems, int __semflg) __THROW;

// /* Operate on semaphore.  */
// extern int semop (int __semid, struct sembuf *__sops, size_t __nsops) __THROW;

// #ifdef __USE_GNU
// /* Operate on semaphore with timeout.  */
// extern int semtimedop (int __semid, struct sembuf *__sops, size_t __nsops,
// 		       const struct timespec *__timeout) __THROW;

// struct sem_buf{
//     short sem_num;  //操作信号在信号集中的编号，第一个信号的编号是0。

//     /*通常只会用到两个值，一个是-1，也就是p操作，它等待信号量变为可用；
//     一个是+1，也就是v操作，它发送信号通知信号量现在可用。
//      sem_op成员的值是信号量在一次操作中需要改变的数值*/
//      short sem_op;

//     short sem_flg; //通常设为：SEM_UNDO，程序结束，信号量为semop调用前的值。
// };

// struct sembuf
// {
//   unsigned short int sem_num;	/* semaphore number */
//   short int sem_op;		/* semaphore operation */
//   short int sem_flg;		/* operation flag */
// };
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo* __buf;
};

void P(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_op = -1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;
    int semop_id = semop (sem_id,&sem_buf,1);
    std::cout<<"semop_id:P:"<<semop_id<<std::endl;
}

void V(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_op = 1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;
    int semop_id = semop (sem_id,&sem_buf,1);
    
    std::cout<<"semop_id:V:"<<semop_id<<std::endl;
}

// int sem_init(sem_t *sem, int pshared, unsigned int value);，其中sem是要初始化的信号量，pshared表示此信号量是在进程间共享还是线程间共享，value是信号量的初始值。
// int sem_destroy(sem_t *sem);,其中sem是要销毁的信号量。只有用sem_init初始化的信号量才能用sem_destroy销毁。
// int sem_wait(sem_t *sem);等待信号量，如果信号量的值大于0,将信号量的值减1,立即返回。如果信号量的值为0,则线程阻塞。相当于P操作。成功返回0,失败返回-1。
// int sem_post(sem_t *sem); 释放信号量，让信号量的值加1。相当于V操作。

int main(int argc,char**argv) {

    sem_t sem_t_;
    int error_code = sem_init(&sem_t_,1,1);


    pid_t pid = fork();
    if(pid < 0) {
        std::cout<<"fork error"<<std::endl;
        goto clean;
    }else if(pid == 0){
        sleep(1);
        sem_wait(&sem_t_);
        std::cout<<"child V over"<<std::endl;
        // P(sem_id);
        sem_post(&sem_t_);
        std::cout<<"child P"<<std::endl;
        // sleep(3);
        // V(sem_id);

    }else{

        // P(sem_id);
        sem_post(&sem_t_);
        std::cout<<"Father P"<<std::endl;
        sleep(5);
        // V(sem_id);
        sem_wait(&sem_t_);
        std::cout<<"Father V Over"<<std::endl;

    }
    //    while(true) {
    //     std::cout<<"Going"<<std::endl;
    //     sleep(1);
    // }

    /*
    struct timespec timer;
    timer.tv_nsec = 0;
    timer.tv_sec = 10;
    semtimedop(sem_id,&sem_buf,sizeof(sem_buf),&timer);
    */

    
clean:
    // semctl(sem_id, 0, IPC_RMID, sem_un);
    ;

    return 0;
}