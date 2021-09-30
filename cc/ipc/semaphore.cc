#include <iostream>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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

int main(int argc,char**argv) {
    key_t sem_key = ftok(".",6543);
    int sem_id = semget(sem_key,1,IPC_CREAT | 0666);
    union semun sem_un;
	sem_un.val = 1;//初始化信号量为1
	semctl(sem_id, 0, SETVAL, sem_un);



 

    
    pid_t pid = fork();
    if(pid < 0) {
        std::cout<<"fork error"<<std::endl;
        goto clean;
    }else if(pid == 0){
        sleep(1);
        P(sem_id);
        std::cout<<"child P"<<std::endl;
        // sleep(3);
        V(sem_id);
        std::cout<<"child V over"<<std::endl;
    }else{

        P(sem_id);
        std::cout<<"Father P"<<std::endl;
        sleep(5);
        V(sem_id);
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
    semctl(sem_id, 0, IPC_RMID, sem_un);

    return 0;
}