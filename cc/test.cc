#include<sys/sem.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>


union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo* __buf;
};

void pv(int sem_id, int op)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = op;
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
}

void P(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_op = -1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;
    int semop_id =  semop(sem_id,&sem_buf,1);
    // semop(sem_id, &sem_buf, 1);
    // std::cout<<"semop_id:P:"<<semop_id<<std::endl;
}

void V(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_op = 1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;
    int semop_id =  semop(sem_id,&sem_buf,1);
    // semop(sem_id, &sem_buf, 1);
    // std::cout<<"semop_id:V:"<<semop_id<<std::endl;
}

int main()
{
	int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0644);
	union semun sem_un;
	sem_un.val = 1;//初始化信号量为1
	semctl(sem_id, 0, SETVAL, sem_un);

	pid_t id = fork();
	if (id < 0)
	{
		return 1;
	}
	else if (id == 0)
	{
        sleep(1);
		printf("child try to get binary sem\n");
		// pv(sem_id, -1);
        P(sem_id);
		// printf("chlid get the sem and release it after 5 seconds\n");
        printf("Child P\n");
		// sleep(5);
		// pv(sem_id, 1);
        V(sem_id);
        printf("Child V\n");
		exit(0);
	}
	else
	{
		printf("parent try to get binary sem\n");
		// pv(sem_id, -1);
        P(sem_id);
        printf("Father P\n");
		// printf("parent get the sem and release it after 5 seconds\n");
		sleep(5);
		// pv(sem_id, 1);
        V(sem_id);
        // printf("Father V\n");
	}
	waitpid(id, NULL, 0);
	// semctl(sem_id, 0, IPC_RMID, sem_un);
	return 0;
}
