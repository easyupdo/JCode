#include <iostream>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//poxis
#include <sys/mman.h>
#include <fcntl.h>

#include <sys/wait.h>

#define TEXT_SZ 1024
// template<uint64_t TEXT_SZ>
typedef struct
{
    int written; // 作为一个标志，非0：表示可读，0：表示可写
    char buf[TEXT_SZ]; // 记录写入 和 读取 的文本
}SHM_BUF;


//     /* Shared memory control operation.  */
// extern int shmctl (int __shmid, int __cmd, struct shmid_ds *__buf) __THROW;

// /* Get shared memory segment.  */
// extern int shmget (key_t __key, size_t __size, int __shmflg) __THROW;

// /* Attach shared memory segment.  */
// extern void *shmat (int __shmid, const void *__shmaddr, int __shmflg)
//      __THROW;

// /* Detach shared memory segment.  */
// extern int shmdt (const void *__shmaddr) __THROW;

//// poxis interface

// /* Open shared memory segment.  */
// extern int shm_open (const char *__name, int __oflag, mode_t __mode);

// /* Remove shared memory segment.  */
// extern int shm_unlink (const char *__name);

// extern void *mmap (void *__addr, size_t __len, int __prot,
// 		   int __flags, int __fd, __off_t __offset) __THROW;

// extern int munmap (void *__addr, size_t __len) __THROW;

int main(int argc,char **argv) {

    int poxis_shm_id = shm_open("poxis_shm",O_CREAT|O_RDWR,0666);

    ftruncate(poxis_shm_id,1024);

    pid_t pid = fork();
    if(pid < 0) {
        std::cout<<"pid:error"<<std::endl;
        goto clean;
    }else if(pid ==0){
        std::cout<<"child pid:"<<pid<<std::endl;

        char * poxis_shm = (char*)mmap(NULL,1024, PROT_READ|PROT_WRITE,MAP_SHARED,poxis_shm_id,0);

        while(true) {
            std::cout<<"wait read"<<std::endl;
            std::cout<<"poxis_shm_read_data:"<<poxis_shm<<std::endl;
            std::cout<<"poxis_shm_read_addr:"<<&poxis_shm<<std::endl;
            sleep(1);
        }
    }else {
        //TODO write

        char * poxis_shm = (char*)mmap(NULL,1024, PROT_READ|PROT_WRITE,MAP_SHARED,poxis_shm_id,0);

        poxis_shm[0] = 'H';
        poxis_shm[1] = 'e';
        poxis_shm[2] = 'l';
        poxis_shm[3] = 'l';
        poxis_shm[4] = 'o';
        poxis_shm[5] = '\0';

        std::cout<<"poxis_shm_write_addr:"<<&poxis_shm<<std::endl;

    }

    int status;
    wait(&status);

    
    
        



clean:
    ;

    return 0;
}