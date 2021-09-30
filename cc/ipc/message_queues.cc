#include <iostream>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <string.h>

#define TEXT_SZ 1024
typedef struct
{
    int written; // 作为一个标志，非0：表示可读，0：表示可写
    char buf[TEXT_SZ]; // 记录写入 和 读取 的文本
}MSG_BUF;

int main(int args,char**argv) {


// /* Message queue control operation.  */
// extern int msgctl (int __msqid, int __cmd, struct msqid_ds *__buf) __THROW;

// /* Get messages queue.  */
// extern int msgget (key_t __key, int __msgflg) __THROW;

// /* Receive message from message queue.

//    This function is a cancellation point and therefore not marked with
//    __THROW.  */
// extern ssize_t msgrcv (int __msqid, void *__msgp, size_t __msgsz,
// 		       long int __msgtyp, int __msgflg);

// /* Send message to message queue.

//    This function is a cancellation point and therefore not marked with
//    __THROW.  */
// extern int msgsnd (int __msqid, const void *__msgp, size_t __msgsz,
// 		   int __msgflg);

    key_t msg_key=ftok(".",5432);
    int msg_id = msgget(msg_key,IPC_CREAT | 0666);
    perror("msgget");

    pid_t pid = fork();
    if(pid < 0) {
        std::cout<<"pid:fork error!"<<std::endl;
        goto clean;
    }else if(pid == 0){
        std::cout<<"Child"<<std::endl;
        char ch[]="HelloMsg";
        MSG_BUF msg_buf;
        memcpy(msg_buf.buf,ch,8);
        msg_buf.written = 1;
        
        int msg_send = msgsnd(msg_id,(void*)&msg_buf,sizeof(MSG_BUF),IPC_NOWAIT);
        std::cout<<"msg send"<<msg_send<<std::endl;
    }else {
        std::cout<<"Father"<<std::endl;
        char ch[1024];
        bzero(&ch,1024);
        MSG_BUF msg_buf;
        while(true) {
            msgrcv(msg_id,&msg_buf,sizeof(MSG_BUF),0,IPC_NOWAIT);
            if(msg_buf.written == 1){
                std::cout<<"read data:"<<msg_buf.buf<<std::endl;
                break;
            }
        }
    }


clean:
    // msgctl(msg_id,NULL,0);

    return 0;
}