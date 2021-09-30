#include <iostream>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define TEXT_SZ 1024
// template<uint64_t TEXT_SZ>
typedef struct
{
    int written; // 作为一个标志，非0：表示可读，0：表示可写
    char buf[TEXT_SZ]; // 记录写入 和 读取 的文本
}SHM_BUF;

int main(int argc,char **argv) {

//     /* Shared memory control operation.  */
// extern int shmctl (int __shmid, int __cmd, struct shmid_ds *__buf) __THROW;

// /* Get shared memory segment.  */
// extern int shmget (key_t __key, size_t __size, int __shmflg) __THROW;

// /* Attach shared memory segment.  */
// extern void *shmat (int __shmid, const void *__shmaddr, int __shmflg)
//      __THROW;

// /* Detach shared memory segment.  */
// extern int shmdt (const void *__shmaddr) __THROW;

    key_t shm_key=ftok(".",4321);
    size_t shm_size = 1024;

    int shm_id = shmget(shm_key,sizeof(SHM_BUF),IPC_CREAT|0666);

    if(shm_id == -1) 
        std::cout<<"shmget error"<<std::endl;
    void* shm_mem = shmat(shm_id,NULL,0);
    perror("shmat");

    
    SHM_BUF* shm_buf = (SHM_BUF*)shm_mem;
    char ch[] = "Hello";
    memcpy(shm_buf->buf,ch,5);
    shm_buf->written = 1;
    


    if(shm_buf->written){
        std::cout<<"flag:"<<shm_buf->written<<std::endl;
        std::cout<<"buf:"<<shm_buf->buf<<std::endl;
    }

    pid_t pid = fork();
    if(pid < 0) {
        std::cout<<"pid:error"<<std::endl;
        goto clean;
    }else if(pid ==0){
        std::cout<<"child pid:"<<pid<<std::endl;
        if(shm_id == -1) 
        std::cout<<"shmget error"<<std::endl;
        void* shm_mem = shmat(shm_id,NULL,0);
        perror("shmat");

        
        SHM_BUF* shm_buf = (SHM_BUF*)shm_mem;
        char ch[1024];
        while(true) {
            std::cout<<"wait read"<<std::endl;
            if(shm_buf->written) {
                memcpy(ch,shm_buf->buf,5);
                std::cout<<"read data:"<<shm_buf->buf<<std::endl;
                break;
            }
        }
    }else {
        //TODO write
        std::cout<<"father pid:"<<pid<<std::endl;
        if(shm_id == -1) 
        std::cout<<"shmget error"<<std::endl;
        void* shm_mem = shmat(shm_id,NULL,0);
        perror("shmat");

        SHM_BUF* shm_buf = (SHM_BUF*)shm_mem;
        char ch[] = "Hello";
        memcpy(shm_buf->buf,ch,5);
        shm_buf->written = 1;
    }
    
        



clean:
    shmdt(shm_mem);

    shmctl(shm_id,IPC_RMID,0);

    return 0;
}