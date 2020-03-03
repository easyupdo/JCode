/*ASCII*/
/*#include <stdio.h>
#include <malloc.h>
int main()
{
	int num;
	int i = 0;
	int tmp = 0;
	char *p;
	scanf("%d",&num);
	p = (char *)malloc(3*num*sizeof(char));
	for(i=0;i<num;i++)
	{	getchar();
		scanf("%c%c%c",p+3*i,p+1+3*i,p+2+3*i);
		//printf("%c %c %c",*(p+i*3),*(p+1+i*3),*(p+2+i*3));
	}
	
	for(i=0;i<num;i++)
	{
		if(*(p+i*3)>*(p+1+i*3))
		{
			tmp = *(p+i*3);
			*(p+i*3) = *(p+1+i*3);
			*(p+1+i*3) = tmp;
		}
		if(*(p+i*3)>*(p+2+i*3))
		{
			tmp = *(p+i*3);
			*(p+i*3) = *(p+2+i*3);
			*(p+2+i*3) = tmp;
		}
		if(*(p+1+i*3)>*(p+2+i*3))
		{
			tmp = *(p+1+i*3);
			*(p+1+i*3) = *(p+2+i*3);
			*(p+2+i*3) = tmp;
		}
	}
	
	for(i = 0;i<num;i++)
	printf("%c %c %c\n",*(p+i*3),*(p+1+i*3),*(p+2+i*3));
}
*//*
#include "stdio.h"
main()
{
char a,b,c,d;
int i;
scanf("%d",&i);
getchar();
while(i--)
{
scanf("%c%c%c",&a,&b,&c);
getchar();
if (a>b) {d=a;a=b;b=d;}
if (a>c) {d=a;a=c;c=d;}
if (b>c) {d=b;b=c;c=d;}
printf("%c %c %c\n",a,b,c);
}

}*/
/*Prime summation*/
/*
#include <stdio.h>
#include <malloc.h>
int main()
{
	int Znum=0,Cnum=0,Snum,sum = 0;
	int i=0,j=0,k=0;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		sum = 0;
		scanf("%d",&Cnum);
		for(j=0;j<Cnum;j++)
		{	
			scanf("%d",&Snum);
			//printf("a%d ",Snum);
			getchar();
			for(k=2;k<=Snum;k++)
			if(Snum%k ==0)
			{
				if(k<Snum)
				break;
				else
				{
				sum = sum + k;
				
				}
				
			}
			
			
		}
		printf("%d\n",sum);
	}	
}
*/


/*
#include<stdio.h>  
#include<string.h>  
#define MAXSIZE 1001  
int prime[MAXSIZE];  
//素数表  
void Prime()
{  int i,j;
    memset(prime,0,sizeof(prime));  
    for(i = 2;i < MAXSIZE;i++){  
        //非素数跳过  
        if(prime[i]){  
            continue;  
        }  
        else{  
            for(j = i*i;j < MAXSIZE;j += i){  
                prime[j] = 1;  
            }  
        }  
    }  
}  
  
int main()  
{  
    int N,i,M,sum,x;  
    //freopen("C:\\Users\\SJF\\Desktop\\acm.txt","r",stdin);  
    scanf("%d",&N);  
    //素数表  
    Prime();  
    prime[1] = 1;  
    prime[0] = 1;  
    //N组测试数据  
    while(N--)
    {  
        sum = 0;  
        //M个数据  
        scanf("%d",&M);  
        for(i = 0;i < M;i++){  
            scanf("%d",&x);  
            //素数相加  
            if(prime[x] == 0){  
                sum += x;  
            }  
        }  
        printf("%d\n",sum);  
    }  
    return 0;  
}  

*/
/*****Take stones******/
/*
#include <stdio.h>
int main()
{
	int Znum=0,i=0,k=0,j=0;
	int rule[2]=0;
	int sum=0;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		scanf("%d%d",&rule[0],&rule[1]);
		while(rule[0] - sum)
		{
			for(j=1;j<rule[2];j++)
			{
					
				for(k=1;k<rule[2];k++)
				{
					sum = j+k;
					if(sum >= rule[0])
					{
						printf("Win\n");
						break;		
					}			
				}
		
			}
		}
		
		
	}
}
*/
/*
#include <stdio.h>

int isPrime(int num)  
{  
	int i;
    if(num==1)return 0;  
    for(i=2;i*i<=num;i++)  
        if(num%i==0)  
            return 0; //N  
    return 1;   //Y
}

int main()
{
	int Znum,Snum;
	int p1=0,p2=0;
	int i = 0,j = 0;
	int x=0;
	scanf("%d",&Znum);
	for(;i<Znum;i++)
	{
		
		scanf("%d",&Snum);
		if(isPrime(Snum))
		{
			printf("%d %d\n",Snum,0);
		}else
		{
			for(j=Snum;j>1;j--)
			{
				
				if(isPrime(j))
				{
					p1=j;		
					break;
				}
			}
			for(j=Snum;;j++)
			{
				if(isPrime(j))
				{
					p2=j;		
					break;
				}
			}
			if(p2 ==2)
			printf("%d %d\n",p2,p2-Snum);
			else
			if(p2-Snum >= Snum-p1)
			printf("%d %d\n",p1,Snum-p1);
			else
			printf("%d %d\n",p2,p2-Snum);	
		}
	}	
}

*/

/*
#include <stdio.h>
int main()
{
	int Znum,Snum;
	int j,i,k;
	scanf("%d",&Znum);
	for(i=0;i<Znum;i++)
	{
		scanf("%d",&Snum);//1000000
		for(j=Snum;j>2;j--)
		{
			for(k=2;k<=Snum;k++)
			if(j%k == 0)
			{
				if(k < j)
				break;
			}
		}
		
		
	}
}
*/









/*


#include<stdio.h>  
#include<stdlib.h>  
  
int isPrime(int num)  
{  
	int i;
    if(num==1)return 0;  
    for(i=2;i*i<=num;i++)  
        if(num%i==0)  
            return 0;  
    return 1;  
}  
  
int main()  
{  
    int n,num,numUp,numDown,deltUp,deltDown;  
    scanf("%d",&n);  
    while(n--)  
    {  
        scanf("%d",&num);  
        if(isPrime(num))//本身是素数，后面就不用了   
          printf("%d 0\n",num);  
        else  
        {  
            numUp=numDown=num;  
            while(!isPrime(numUp))  
            {  
                numUp+=1;  
            }  
            while(!isPrime(numDown)&&numDown>0)//边界条件，否则不能通过   
            {  
                numDown-=1;  
            }  
            deltUp = numUp-num;  
            deltDown = num-numDown;  
              
            if(numDown==0)//特殊情况：左边没有找到   
              printf("%d %d\n",numUp,deltUp);  
            else if(deltUp>=deltDown)//输出距离小的, 相等则左   
                printf("%d %d\n",numDown,deltDown);  
            else  
                printf("%d %d\n",numUp,deltUp);  
        }  
  
    }  
    //system("PAUSE");  
    return 0;  
}  
*/
/*
#include<iostream>
#include<cmath>
using namespace std;
bool isprime(int n)
{
for(int k=2;k<=sqrt((double)n);k++)
if((n%k)==0)
return false;
return true;
}
int main()
{
int n;
cin>>n;
while(n--)
{
int num,i,j;       
cin>>num;
if(num==1)
{
cout<<"2 1"<<endl;
continue;
}
for(i=num;!isprime(i);i--);
for(j=num;!isprime(j);j++);
if((num-i)<(j-num))
cout<<i<<' '<<(num-i)<<endl;
else if((num-i)>(j-num))
cout<<j<<' '<<(j-num)<<endl;
else if((num-i)==(j-num))
cout<<i<<' '<<(num-i)<<endl;
}
}
*/


/*
#include <stdio.h>
int main()
{
	int Znum;
	int i,j;
	int arr[9];
	int narr[3][3]={0};
	scanf("%d",&Znum);
	while(Znum--)
	{
		for(i=0;i<9;i++)
		{
			scanf("%d",&arr[i]);
		}	
		for(i=0;i<3;i++)
		{
			narr[i][0]=arr[i];
			narr[i][1]=arr[i+3];
			narr[i][2]=arr[i+6];	
			printf("%d ",narr[i][0]);
			printf("%d ",narr[i][1]);
			printf("%d ",narr[i][2]);
			
			printf("\n");
		}
	
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			printf("%d ",narr[i][j]);
			printf("\n");
		}
		
	}
}
*/
/*
#include <stdio.h>
#define symbols 10001
int main()
{
	int N,M;
	int L,R;
	int Znum;;
	int i;
	int sum = 0;
	int Last[symbols]={0};
	int flag = 0;
	scanf("%d",&Znum);
	while(Znum--)
	{
		sum=0;
		
		scanf("%d %d",&N,&M);
		while(M--)
		{
			flag =0;
			scanf("%d",&L);
			getchar();
			scanf("%d",&R);
			getchar();
			//printf("%d %d",L,R);
			for(i=L;i<=R;i++)
			{
				Last[i] = 1;
				flag++;
			}	
		printf("FFFFFFF%d\n",flag);
		
		}
			for(i=0;i<=10000;i++)
			{
				if(Last[i])
				{
					sum++;
					printf("%d-%d ",i,Last[i]);
				}
			}
			printf("SSSSSSSS%d\n",sum);
			printf("LLLL%d\n",N-sum);
	}
}
*/
/*
#include <iostream>  
using namespace std;  
int main()  
{  
    int n;  
    cin>>n;  
    while(n--){  
        int L,m,w,q,num=0;  
        cin>>L;  
        int a[L+1];  
        cin>>m;  
        for(int i=0;i<L+1;i++){  
            a[i]=0;  
        }  
        for(int i=0;i<m;i++){  
            cin>>w>>q;  
            for(int i=w;i<=q;i++){  
                a[i]=1;  
            }  
        }  
  
        for(int i=0;i<L+1;i++){  
            if(a[i]==0){  
                num++;  
            }  
        }  
        cout<<num<<endl;  
    }  
    return 0;  
}  


*/
/*
#include <stdio.h>
int main()
{
	int N;
	int i,j,k;
	int arr[2];
	int account = 0;
	scanf("%d",&N);
	while(N--)
	{	
		account = 0;
		scanf("%d",&arr[0]);
		getchar();
		scanf("%d",&arr[1]);
		getchar();
		for(i=arr[0];i>0;i--)
		{
			k = i;
			while(1)
			{
				if(!(k%arr[1])) //if==0
				{
					k = k/arr[1];
					account+=1;;
				}else
				break;
			}
		}
		printf("%d\n",account);
	}
}


*/

/*
#include <stdio.h>

int * sortFindMaxandMin(int num, int M[])
{
	int i,j;
	int arr[4];//1234
	int tmp=1;
	int max = 0;
	int min =0;
	M[1]=M[0] = 0;
	for(i=3;i>=0;i--)
	{
		arr[i] = (num) % 10; //4
		num = (num)/10;
	}
	for(i=0;i<4;i++)
	{	
		for(j=i+1;j<4;j++)
		if(arr[i]<arr[j])
		{
			tmp=arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}	
	}
	for(i=0;i<4;i++)
	tmp =1;
	for(i=2;i>=0;i--)//4 ci //Max
	{
		tmp = 10*tmp;
		M[0] = arr[i]*tmp + M[0];
	}
	M[0] = M[0]+arr[3];
	tmp = 10000;
	for(i=3;i>=0;i--)       //Min
	{
		tmp = tmp/10;
		M[1] = arr[i]*tmp + M[1];
	}	
	
	return M;
		
}


int main()
{
	int N;
	int i,j;
	int arr;	
	int max;
	int tmp;
	int k;
	int M[2] = {0};
	int account = 0;
	scanf("%d",&N);
	while(N--)
	{
		account =0;
		scanf("%d",&arr);
		getchar();
		sortFindMaxandMin(arr,M);
		tmp= M[0];
		while(1)
		{			
			if(M[0]-M[1] == k)
			{
				break;
			}	
			else
			{
				
				k = tmp;
				tmp = M[0]-M[1];
				sortFindMaxandMin(tmp,M);
				account+=1;
			}
		}	
		
		printf("%d\n",account);
	}
}

*/

/*################### Interprocess communication ####################*/
//1.pipe
/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
	char *childstring = "This is send form child !";
	int fd[2];
	char buf[100]={0};
	pipe(fd);
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		printf("Fork is ERROR ! exit");
		exit(1);
	}
	if(pid == 0)
	{
		printf("This is child process!\n");
		close(fd[0]);//close the read pipe
		write(fd[1],argv[1],strlen(argv[1]));
		close(fd[1]);	
		
	}else
	{
		memset(buf,0,100);
		printf("This is father process!\n");
		close(fd[1]);
		read(fd[0],buf,100);
		close(fd[0]);
		printf("Buf size=%d\n",sizeof(buf));
		printf("%s\n",buf);
	}
	waitpid( pid, NULL, 0 );
}

*/
//Famous pipe
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>


#define FIFO /usr/work/workspace/FUCKYOU/fifo
int main()
{
	int account =55;
	char * string = "This is test mkfifo!";
	pid_t pid2,pid1;
	int fd;
	int fd2;
	char buf[100];
	pid1 = fork();
	if(pid1 == 0)//child
	{
		memset(buf,0,sizeof(buf));
		printf("This is Pid1 child process! pid1==%d\n",getpid());
		printf("The pid1 father process ID:%d\n",getppid());
		fd = open("FIFO",O_RDONLY );
		read(fd,buf,sizeof(buf));
		close(fd);
		
		printf("%s\n",buf);
		printf("account==%d\n",account);
	}
	
	pid2 = fork();
	if(pid2 ==0)
	{
		printf("This is Pid2 child process! pid2==%d\n",getpid());
		printf("The pid2 father process ID:%d\n",getppid());
		fd2 = open("FIFO",O_WRONLY);
		write(fd2,string,strlen(string));
		close(fd2);
		account+=1;
		printf("account==%d\n",account);	
	}

	waitpid(NULL);	
	
}
*/
//
/*
#include <signal.h>
#include <stdio.h>
int account =55;
void sigHandel(int sig)
{
	if(sig ==SIGUSR1)
	account+=1;
	if(sig == SIGUSR2)
	account = 100;
}
int main()
{
	int signum;
	pid_t pid;
	signal(SIGUSR1,sigHandel);
	signal(SIGUSR2,sigHandel);
	pid = fork();
	if(pid == 0)
	{
		printf("child process ID:%d father process ID:%d\n",getpid(),getppid());
		kill(getppid(),SIGUSR2);
		printf("TTTT%d\n",account);
	}
	else
	{
		sleep(1);
		printf("father process ID:%d  account:%d\n",getpid(),account);	
	}
	waitpid(NULL);
	return 0;
	
}



*/
/*
#include <stdio.h>
struct tree
{
	int a;
};

void fun()
{
	printf("This is fun!\n");
}


int a;
const int c = 10;
int main()
{
static int b;

	//char *p;
	//char arr[]="dweqrgfsrwh";
	//p = F();
	//p = arr;
	//p[0]=L';
	//printf("%s\n",p);
	
	void (*F)();
	
	char *p;
	char arr[]="asdfghjkl";
	p = arr;
	struct tree T;	
	printf("a == %d\n",++a);
	printf("b == %d\n",++b);	
	printf("c == %d\n",c);
	printf("%x\n",T);
	printf("p==%x",p);
	printf("&arr==%x\n",&arr);
	printf("&arr[0]==%x\n",&arr[0]);
	printf("++++++++++++++++++++++++\n");
	
	F =&fun;
	F();
	
	printf("fun == %x\n",fun);
	printf("fun == %x\n",&fun);
	
}

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
// 1.
/*
typedef struct huffManTree
{
	int weight;
	char word;
	struct huffManTree *lchild,*rchild;

}tree;
*/
//2.
/*
功能:huffManTree节点信息  此在生成huffman编码后会销毁
*/
typedef struct HFTree
{
	int weight;        //huffManTree节点信息
	int lchild,rchild;//在huffman树中记录左右子树 (用户输入结构中的下标)
}HFTree;

/*
功能:用户输入节点信息
*/
typedef struct node
{
	int info_weight;            //权值
	char info_word;		    //字符
	char info_huffmanCode[256]; //huffman编码
}node;

/*
功能:将用户输入的信息根据权值从小到大排序
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
返回值:返回权值最小的叶子节点	
*/
void sortMinToMax(node*pnode,int N)
{
	int i,j;
	int tmp_weight;
	char tmp_word;
	node * rootPnode,*parperPnode;
	rootPnode = pnode;
	for(i=0;i<N;i++)
	{
		pnode = parperPnode = rootPnode;
		
		for(j=1;j<N;j++)
		{
			parperPnode = pnode;
			pnode +=1;
			if(parperPnode->info_weight > pnode->info_weight)
			{
				printf("parperPnode=%d ",parperPnode->info_weight);
				printf("pnode=%d \n",pnode->info_weight);
				tmp_weight = parperPnode->info_weight;
				parperPnode->info_weight = pnode->info_weight;
				pnode->info_weight = tmp_weight;
			
				tmp_word = parperPnode->info_word;
				parperPnode->info_word = pnode->info_word;
				pnode->info_word = tmp_word;
			}
		}
	}
}

/*
功能:查找用户输入的权值最小的叶子
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
	HFTree*rootHuffmanTree:生成的huffman树根节点
返回值:返回权值最小的叶子节点	
*/
node * findMinNode(node * pnode ,int N,int k)
{
	int i;
	sortMinToMax(pnode,N);//first step :sort
	node * rootTree;
	node * minNode;
	//minNode->info_weight = pnode[k].info_weight;
	minNode = &pnode[k];
	for(i=k;i<N;i++)
	{
		if(minNode->info_weight > pnode[i].info_weight)
		minNode->info_weight = pnode[i].info_weight;
	}

return minNode;	
}

/*
功能: 根据huffman树生成huffman编码
参数:
	pnode * pnode         :保存权值和字符的结构地址
	int N                 :用户输入字符个数
	HFTree*rootHuffmanTree:生成的huffman树根节点
*/
void huffmanCodeing(node * pnode,int N,HFTree *rootHuffmanTree)
{
	char *code;
	char *codeT;
	char codeF[256];
	char codeL[256];
	char codeR[256];
	int k = 0,i;
	//生成huffman编码
	memset(codeF,0,sizeof(codeF));
	memset(codeL,0,sizeof(codeL));
	memset(codeR,0,sizeof(codeR));
	for(i=N-2,k=0;i>=0;i--,k++)//
	{
		if(rootHuffmanTree[i].rchild == -1 )
		{
			code = "0";//zuo L
			codeT= "1" ;
			
			strcpy(codeL,codeF);//codeL = codeF  + code;
			strcat(codeL,code);
			strcat(codeF,codeT);//codeF = codeF + codeT;	
#ifdef DEBUG
			printf("LLLL%s\n",codeL);
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeL);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
		}else
		if(rootHuffmanTree[i].lchild == -1)
		{
			
			code = "1";//you R
			codeT= "0";
			
			strcpy(codeR,codeF);//codeR = codeF  + code;
			strcat(codeR,code);
			strcat(codeF,codeT);//codeF = codeF + codeT;	
#ifdef DEBUG	
			printf("RRR%s\n",codeR);
#endif	
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
		}else
		{
			code = "1";//you R
			codeT= "0" ;
			
			strcpy(codeL,codeF);//codeL = codeF + 0;
			strcat(codeL,codeT);
			
			strcpy(codeR,codeF);//codeL = codeF + 0;
			strcat(codeR,code);//codeR = codeF + 1;
			strcpy(pnode[i].info_huffmanCode,codeL);
			strcpy(pnode[i+1].info_huffmanCode,codeR);//根据huffman树生成编码保存到节点结构的info_huffmancode字段中
#ifdef DEBUG
			printf("LLLL%s\n",codeL);
			printf("RRRR%s\n",codeR);
#endif
		}
	}
	free(rootHuffmanTree);
}
/*
功能:生成huffman树
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/
HFTree * createHuffmanTree(node * pnode,int N)
{
	int i;
	int account=0;
	HFTree * rootHuffmanTree,*tmpLinkTree;
	node *firstPnode,*secondPnode;
	secondPnode = pnode;
	firstPnode = (node*)malloc(sizeof(node));
	firstPnode->info_word='T';
	tmpLinkTree = rootHuffmanTree = NULL;
	rootHuffmanTree = (HFTree*)malloc((N-1)*sizeof(HFTree));
	for(i=1;i<N;i++)
	{
		if(i == 1)
		{
			firstPnode->info_weight = secondPnode->info_weight;
		
		}
		else
		{
			firstPnode->info_weight = rootHuffmanTree->weight;
		}
		

		secondPnode = findMinNode(pnode,N,i);//second step:find min node
		tmpLinkTree = rootHuffmanTree;
		
		rootHuffmanTree->weight = firstPnode->info_weight + secondPnode->info_weight;
		//memset(rootHuffmanTree->huffmanCode,0,sizeof(rootHuffmanTree->huffmanCode);//
		//生成huffman树
		if(i == 1)
		{
			rootHuffmanTree->lchild = 0;
			rootHuffmanTree->rchild = (secondPnode - pnode);	
		}
		else if(firstPnode->info_weight < secondPnode->info_weight)//firstPnode两个权值最小的叶子生成的和节点  secondPnode是剩下叶子中 权值最小的
		{
			//rootHuffmanTree
			//printf("走右子树\n");
			rootHuffmanTree[i-1].rchild = (secondPnode-pnode);
			rootHuffmanTree[i-1].lchild = -1;
		}else
		{
			//printf(" 走左子树\n");
			rootHuffmanTree[i-1].lchild = (secondPnode - pnode);
			rootHuffmanTree[i-1].rchild = -1;
		}	
	}
	return rootHuffmanTree;
}
/*
功能:解码
参数:
	pnode * pnode:保存权值和字符的结构地址
	int N        :用户输入字符个数
*/
void huffmanDecoding(node*rootPnode,int N)
{
	int i = 0;
	char userDecoding[20];
	char ch;
	int num;
	int x;
	printf("Please input huffmanCode\n");//输入huffman以解码
	getchar();
	while((ch = getchar()) != '\n')
	{
		userDecoding[i++] =ch; 
	}
	userDecoding[i] = '\0';
	num = strlen(userDecoding);
	
	if(N-num > 1)
	{
		printf("编码:%s  字符:%c\n",userDecoding,rootPnode[N - num].info_word);
	}else
	{
		if(!strcmp(userDecoding,rootPnode[0].info_huffmanCode))
		{
			printf("编码:%s  字符:%c\n",userDecoding,rootPnode[0].info_word);	
		}else
		if(!strcmp(userDecoding,rootPnode[1].info_huffmanCode))
		{
			printf("编码:%s  字符:%c\n",userDecoding,rootPnode[1].info_word);
		}
	}
}

int main(int argc,char *argv[])
{
	int N;
	int i,j;
	int weight;
	char word;
	node *pnode,*rootPnode;
	HFTree * rootHuffmanTree;
	printf("Please input the NODE num!\n");
	scanf("%d",&N);
	rootPnode = pnode = (node*)malloc(N*sizeof(node));
	for(i=0;i<N;i++)
	{
		scanf("%d %c",&pnode->info_weight,&pnode->info_word);
		memset(pnode->info_huffmanCode,0,sizeof(pnode->info_huffmanCode));
		pnode++;
		
	}
	rootHuffmanTree = createHuffmanTree(rootPnode,N);
	huffmanCodeing(rootPnode,N,rootHuffmanTree);
	for(i=0;i<N;i++)
//#ifdef DEBUG
	printf("权值:%d  字符:%c  编码:%s\n",rootPnode[i].info_weight,rootPnode[i].info_word,rootPnode[i].info_huffmanCode);
	//解码//输入huffman以解码
	huffmanDecoding(rootPnode,N);
//#endif
//MYDEBUG;
}
/*
example:
4
1 a
2 b
5 c
7 d
权值:1  字符:a  编码:100
权值:2  字符:b  编码:101
权值:5  字符:c  编码:11
权值:7  字符:d  编码:0
root@ubuntu:/usr/work/workspace/CPP/Huffman/Test#

//***********************************************从文件内容筛选内容****************************************************
*/
/*
1.net 2
2.net 3.net
   4.net
5.net

读取出来为：
1.net
22.net
3.net
4.net
5.net
过滤掉空格
*/
 //输出指定文件 当前输出net和wav文件
//读取文件 判断以net和换行为一个文件结束符号
void GetAllNetAndWavFileName(string net_list_file,vector<string> &net_list,string & wav_file)
{
	string line;
	string file;
	ifstream in_stream;
	char buffer[1024];
	char ch[3];
	memset(buffer,0,1024);
	in_stream.open(net_list_file);
	if (in_stream.is_open())
	{
			bool newline = false;
		while (!in_stream.eof())
		{
			getline(in_stream, line);//不读取换行符
			if (line.size() <= 0)
				continue;
			newline = true;
			const char * cline = line.data();
			for (int i = 0;i<line.size();i++)
			{
				if (cline[i] != ' ')
				{
					file = file + cline[i];
				}else
				{
					if (file.size() > 0)
					{
						if (IsNetFile(file))
							net_list.push_back(file);
						else if (IsWavFile(file))//wav
							wav_file = file;
						else//others
							net_list.push_back(file);
						file.clear();
					}
				}
			}
			if (IsNetFile(file))//if 一行结束 if是换行 判断是不是文件
				net_list.push_back(file);
			if (IsWavFile(file))
				wav_file = file;
			file.clear();
		}
	}
	else
	{
		cout << "cannot open nets.list";
	}

}


//判断所有文件
//如果文件名于文件名之间有空格的话就当为是一个文件，换行的话也当为一个文件
void GetAllFileName(string net_list_file, vector<string> &net_list, string & wav_file)
{
	string line;
	string file;
	ifstream in_stream;
	char buffer[1024];
	char ch[3];
	memset(buffer, 0, 1024);
	in_stream.open(net_list_file);
	if (in_stream.is_open())
	{
		bool newline = false;
		while (!in_stream.eof())
		{
			getline(in_stream, line);//不读取换行符
			if (line.size() <= 0)
				continue;
			newline = true;
			const char * cline = line.data();
			for (int i = 0; i<line.size(); i++)
			{
				if (cline[i] != ' ')
				{
					file = file + cline[i];
				}
				else
				{
					if (file.size() > 0)//分类器
					{
						if (IsNetFile(file))//net
							net_list.push_back(file);
						else if (IsWavFile(file))//wav
							wav_file = file;
						else//others
							net_list.push_back(file);
							file.clear();
					}
				}
			}
			if (IsNetFile(file))
			{
				net_list.push_back(file);
				file.clear();
			}
			else
			{
				net_list.push_back(file);
				file.clear();
			}
		}
	}
	else
	{
		cout << "cannot open nets.list";
	}

}



//组装字节序 responser是组装好的字节序
void test(int length,int data_length ,char data)
{
	string responser;
	responser = responser + (char)129;//first byte;
	if (length < 126)
		responser = responser + (char)(length) + data;
	else if (length == 126)
	{
		uint16_t data_num = data_length;
		responser = responser + (char)(126) + (char)data_num + (char)(data_num >> 8) + data;
	}
	else if (length == 127)
	{
		uint64_t data_num = data_length;
		responser = responser + (char)(127) + (char)data_num + (char)(data_num >> 8) +
			(char)(data_num >> 16) + (char)(data_num >> 32) + (char)(data_num >> 32) +
			(char)(data_num >> 40) + (char)(data_num >> 48) + (char)(data_num >> 56) + data;
	}


	string filename = "E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\Net_PartABC\\net_part_c_libuv\\work\\responser.info";
	std::ofstream ofs(filename, std::ios::app | std::ios::binary);
	if (ofs.is_open())
	{
		ofs.write(responser.c_str(), responser.size());
	}
	else
		std::cout << errno;
	ofs.close();
}
####
# 切分单词
# 输入：string str = "HOW ARE YOU";
# 输出： HOW  ARE  YOU
######
int sent2words(const std::string &sent, std::vector<string> *words) {

      size_t pos_s = 0;
        size_t pos_e = 0;

          while ((pos_e = sent.find(" ", pos_s)) != std::string::npos) {
                  words->push_back(sent.substr(pos_s, pos_e - pos_s));
                      pos_s = pos_e + 1;
                        }   
            if (pos_s < sent.size())
                  words->push_back(sent.substr(pos_s, sent.size() - pos_s));

              return 0;
}


linux下发布二进制.
**********************************cpldd.sh***********************************************
**********************************功能：拷贝依赖文件****************************************
**********其中，第一个参数代表的是你的可执行文件的名称，第二个参数表示你要导入的目录*****************
#!/bin/bash
# Author : Hemanth.HM
# Email : hemanth[dot]hm[at]gmail[dot]com
# License : GNU GPLv3
#
 
function useage()
{
    cat << EOU
Useage: bash $0 <path to the binary> <path to copy the dependencies>
EOU
exit 1
}
 
#Validate the inputs
[[ $# < 2 ]] && useage
 
#Check if the paths are vaild
[[ ! -e $1 ]] && echo "Not a vaild input $1" && exit 1
[[ -d $2 ]] || echo "No such directory $2 creating..."&& mkdir -p "$2"
 
#Get the library dependencies
echo "Collecting the shared library dependencies for $1..."
deps=$(ldd $1 | awk 'BEGIN{ORS=" "}$1\
~/^\//{print $1}$3~/^\//{print $3}'\
 | sed 's/,$/\n/')
echo "Copying the dependencies to $2"
 
#Copy the deps
for dep in $deps
do
    echo "Copying $dep to $2"
    cp "$dep" "$2"
done
 
echo "Done!"
**********************************cpldd.sh****************************************

// #cpp
//add jay
void ToLower(std::string *word) {
  std::transform(word->begin(), word->end(), word->begin(), ::tolower);
}

void RemoveEndOtherSymbols(std::string *word) {
  int32 last_ch_len = word->length();
  char last_ch = word->c_str()[last_ch_len - 1];
  if (last_ch == 46 || last_ch == 44 || last_ch == 33 || last_ch == 63 ||
      last_ch == 59 || last_ch == 34 || last_ch == 42 || last_ch == 58)
    *word = word->substr(0, last_ch_len - 1);
}

void StringSplit(const std::string &str, std::vector<std::string> *words) {
  size_t pos_s = 0;
  size_t pos_e = 0;
  while (pos_e != std::string::npos) {
    pos_e = str.find(" ", pos_s);
    if (pos_e == pos_s) {
      pos_s += 1;
      continue;
    }
    std::string word = str.substr(pos_s, pos_e - pos_s);
    RemoveEndOtherSymbols(&word);
    ToLower(&word);
    words->push_back(word);
    pos_s = pos_e + 1;
  }
  if (pos_s == std::string::npos) {
    std::string word = str.substr(pos_s, str.size() - pos_s);
    RemoveEndOtherSymbols(&word);
    ToLower(&word);
    words->push_back(word);
  }
}

std::string GetMD5 (const char *data, const int32_t data_len) {
  polly::MD5 md5;
  md5.update(data, data_len);
  md5.Set_finalized_Inti_Status();
  md5.finalize();
  return md5.md5_();
}
int32_t GetMD5(const char *file, std::string *md5_str) {
  std::ifstream jifs(file);
  if (!jifs.is_open()) {
    std::cout << "not open" << std::endl;
    return kErrorOpenFileFailed;
  }
  std::string jmd5((std::istreambuf_iterator<char>(jifs)),
                   std::istreambuf_iterator<char>());
  *md5_str = GetMD5(jmd5.c_str(), jmd5.length());
  return kErrorSuccess;
}

// Use c && c++  >> main for dir(true)
bool IsDirOrFile(const char*f) {
  if (!access(f, 0 | 6)) {
    std::ofstream ofs(f);
    if (!ofs.is_open()) {
      std::cout << "is Open" << std::endl;
      return true;
    } else {
      std::cout << "is Not Open" << std::endl;
      return false;
    }
  }
}
// # 多线程
/*************************************************************************
    > File Name: lsx-ases-pass.cc
    > Author: JayGuan
    > Mail:
    > Created Time: 2019年12月18日 星期三 11时49分28秒
 ************************************************************************/

#include "lsx-ases.h"
#include "../rapidjson/document.h"
#include<iostream>
#include <fstream>
#include <vector>
#include <map>
#include <thread>
#include <assert.h>
#include <algorithm>
#include <cxxabi.h>
#include <execinfo.h>
#include <mutex>

#define HAVE_EXECINFO_H

#define DEBUG 1
#define EVA_DEBUG 1

using namespace std;
using namespace rapidjson;
std::mutex mx;

// LOG

typedef std::string (*StackTraceHandle)();
void SetStackTraceHandle(StackTraceHandle handle);

/***** STACKTRACE *****/

static std::string Demangle(std::string trace_name) {
#if defined(HAVE_CXXABI_H) && defined(HAVE_EXECINFO_H)
  // at input the string looks like:
  //   ./kaldi-error-test(_ZN5kaldi13UnitTestErrorEv+0xb) [0x804965d]
  // We want to extract the name e.g. '_ZN5kaldi13UnitTestErrorEv",
  // demangle it and return it.

  // try to locate '(' and '+', take the string in between,
  size_t begin(trace_name.find("(")),
         end(trace_name.rfind("+"));
  if (begin != std::string::npos && end != std::string::npos && begin < end) {
    trace_name = trace_name.substr(begin + 1, end - (begin + 1));
  }
  // demangle,
  int status;
  char *demangled_name = abi::__cxa_demangle(trace_name.c_str(), 0, 0, &status);
  std::string ans;
  if (status == 0) {
    ans = demangled_name;
    free(demangled_name);
  } else {
    ans = trace_name;
  }
  // return,
  return ans;
#else
  return trace_name;
#endif
}


static std::string StackTrace() {
  std::string ans;
#ifdef HAVE_EXECINFO_H
#define KALDI_MAX_TRACE_SIZE 50
#define KALDI_MAX_TRACE_PRINT 20  // must be even.
  // buffer for the trace,
  void *trace[KALDI_MAX_TRACE_SIZE];
  // get the trace,
  size_t size = backtrace(trace, KALDI_MAX_TRACE_SIZE);
  // get the trace symbols,
  char **trace_symbol = backtrace_symbols(trace, size);

  // Compose the 'string',
  ans += "[ Stack-Trace: ]\n";
  if (size <= KALDI_MAX_TRACE_PRINT) {
    for (size_t i = 0; i < size; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
  } else {  // print out first+last (e.g.) 5.
    for (size_t i = 0; i < KALDI_MAX_TRACE_PRINT / 2; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
    ans += ".\n.\n.\n";
    for (size_t i = size - KALDI_MAX_TRACE_PRINT / 2; i < size; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
    if (size == KALDI_MAX_TRACE_SIZE)
      ans += ".\n.\n.\n";  // stack was too long, probably a bug.
  }

  // cleanup,
  free(trace_symbol);  // it's okay, just the pointers, not the strings.
#endif  // HAVE_EXECINFO_H
  return ans;
}



StackTraceHandle GetStackTrace = StackTrace;
// LOG

using M_LIST = std::multimap<std::string, std::vector<std::string>>;
using T_LIST = std::vector<M_LIST>;
using E_LIST = std::vector<std::thread*>;

bool IsNetFile(string in_file) {
  string file_name = in_file.substr(in_file.find_last_of(".") + 1);
  if (file_name == "net" || file_name == "NET")
    return true;
  else
    return false;
}

bool IsWavFile(string in_file) {
  string file_name = in_file.substr(in_file.find_last_of(".") + 1);
  if (file_name == "wav" || file_name == "WAV")
    return true;
  else
    return false;
}


void ReadListFile(std::string list_file, M_LIST * m_list) {
  std::string line;
  std::string file;
  std::ifstream in_stream;
  std::string net_list_file = list_file;
  using NetList = std::vector<std::string>;
  in_stream.open(net_list_file);
  if (in_stream.is_open()) {
    bool newline = false;
    int session_num = 0;
    while (!in_stream.eof()) {

      std::string wav;
      NetList net_list;
      getline(in_stream, line);//䷾M读住~V彍¢蠾L符
      if (line.size() <= 0)
        continue;
      newline = true;
      const char * cline = line.data();
      for (int i = 0; i < line.size(); i++) {
        if (cline[i] != ' ') {
          file = file + cline[i];
        } else {
          //file = "/home/liping/win10/300/"+ file;
          file =  file;
          if (file.size() > 0) {
            if (IsNetFile(file))
              net_list.push_back(file);
            else if (IsWavFile(file))//wav
              if (net_list.size() == 0)
                wav = file;
              else//others
                net_list.push_back(file);
            file.clear();
          }
        }
      }
      //file = "/home/liping/win10/300/" + file;
      file = file;

      //if (IsNetFile(file))//if ䷾@蠾L纾S彝~_ if彘¯彍¢蠾L 佈¤彖­彘¯䷾M彘¯彖~G件
      if (IsWavFile(file)) {
        if (net_list.size() == 0)
          wav = file;
      } else
        net_list.push_back(file);
      file.clear();
#if DEBUG
      std::cout << "net_list:" << net_list.size() << std::endl;
      std::cout << "Session num:" << ++session_num << std::endl;
      std::cout << "WAV:" << wav << " ";
      std::cout << "wav.c_str():" << wav.c_str() << std::endl;
#endif
      m_list->insert(std::pair<std::string, std::vector<std::string>>(wav, net_list));
    }
  }
  /*
    for (auto x : *m_list) {
      std::cout << "XXX" << x.first << std::endl;
      for (auto y : x.second) {
        std::cout << "YYY" << y << std::endl;
      }
    }
    */

}




size_t LoadBalance(M_LIST *m_list, T_LIST *t_list, size_t num_max) {

  size_t x = m_list->size() / (num_max);
  size_t y = m_list->size() % (num_max);


  size_t a_con = 0;
  size_t con = 0;
  size_t l = 0;
  M_LIST sub_m_list;
  for (auto T : *m_list) {
    if (a_con < num_max) {
      sub_m_list.insert(T);
      con += 1;
    } else {
      T_LIST::iterator it = t_list->begin() + l;
      it->insert(T);
      l += 1;
    }
    if (con == x && a_con < num_max) {
      t_list->push_back(sub_m_list);
      con = 0;
      a_con += 1;
      sub_m_list.clear();
    }
    if(x <= 0) {
      t_list->push_back(sub_m_list);
      con = 0;
      sub_m_list.clear();
    }
  }

  /*
  for (auto T : *t_list) {
    std::cout << "T_LIST:" << std::endl;
    for (auto K : T) {
      std::cout << "M:" << K.first << std::endl;
    }t_list
  }
  */

  return t_list->size();
}

void WriteFile(const std::string &wav, const char*result, const size_t &t_count, const std::string &filename) {

  std::ofstream ofs(filename, std::ios::app);
  if (ofs.is_open()) {
    std::cout<<result<<std::endl;
    //
    Document document;
    document.Parse(result);
    assert(document.HasMember("score"));
    assert(document["score"].IsDouble());
    double p_score = document["score"].GetDouble();
    //printf("%g %g\n", document["score"].GetDouble(),endtime);

    std::string pass_result = std::to_string(p_score);

    assert(document.HasMember("isReject"));
    assert(document["isReject"].IsInt());
    int p_isRegect = document["isReject"].GetInt();
    //printf("isRegect%d\n", document["isReject"].GetInt());
    std::string pass_Reject = std::to_string(p_isRegect);


    std::string w_file_str = "wav:" + wav + " " + "score:" + pass_result + " " + "isReject:" + pass_Reject + " " + "count:" + std::to_string(t_count) + "\n";
    ofs << w_file_str;
    ofs.close();
  }
}


void Task(M_LIST m_list, const std::string type, const std::string model_dir, const std::string output_file) {
  int err_code = -1;
  size_t t_count = 0;
  const char *polly_id = LsxAsesStart (model_dir.c_str(), &err_code);
  const char *session_id = LsxAsesSessionBegin(polly_id, type.c_str(), &err_code);

  auto evaluate = [&](std::string wav, std::vector<std::string>net_lists) {
    for (auto net : net_lists) {
#if DEBUG
      std::cout << "Net:" << net << std::endl;
#endif
      err_code = LsxAsesSessionDataIn(session_id, net.c_str(), 0, "path");
      if (err_code)
        std::cout<<GetStackTrace();
    }

    FILE *fp = NULL;
    fp = fopen(wav.c_str(), "rb");
    if (fp != NULL) {
      //exit(1);

      fseek(fp, 0, SEEK_END);
      size_t len = (ftell(fp) - 44) ;
      fseek(fp, 44, SEEK_SET);
      char *data = new char[len];
      size_t nread = fread(data, sizeof(char), len, fp);
      assert(nread == len);
      fclose(fp);
      int vad_status = 0;
      int status = 0;
      err_code = LsxAsesSessionSpeechIn(session_id, data, len, "wav", NULL);
      delete []data;
      if (err_code)
        std::cout<<GetStackTrace();
      int result_len = 0;
      std::lock_guard<std::mutex> locak(mx);
      const char *result = LsxAsesSessionGetResult(session_id, "up366", &result_len, &err_code);
      t_count += 1;

#if DEBUG
      printf("%s\n", result);
#endif
#if EVA_DEBUG
      WriteFile(wav, result, t_count, output_file);
#endif
    } else {
      std::cout << "Wav file open failed!" << std::endl;
    }
  };

  //all
  //std::for_each(m_list->begin(),m_list->end(),evaluate);
  for (M_LIST::const_iterator it = m_list.begin(); it != m_list.end(); ++it) {
    evaluate(it->first, it->second);
  }

}


void ParallelProcess(M_LIST * m_list, E_LIST * e_list, const std::string type, const std::string &model_dir, const std::string &output_file) {
  size_t th_num_max = std::thread::hardware_concurrency();
  th_num_max = 1; //threads num

  int a = 10;
  T_LIST t_list;
  if (LoadBalance(m_list, &t_list, th_num_max) <= th_num_max) {
    for (size_t i = 0; i < t_list.size(); ++i) {
      std::string th_output_file = output_file + "_" + std::to_string(i);
      std::thread *th = new std::thread(Task, (t_list[i]),type, model_dir, th_output_file);
      e_list->push_back(th);
    }
  } else {
    std::cout << "Task > th_num_max" << std::endl;
  }
}

void Usage() {
  std::cout << "*****************************************************************************" << std::endl;
  std::cout << "**** Usage: xxx.exe mession_type model_dir mession_list output_filename ****" << std::endl;
  std::cout << "**** HELP:                                                              ****" << std::endl;
  std::cout << "****    mession_type:parta/partb/partc                                  ****" << std::endl;
  std::cout << "****    mession_list format: xxx.wav xxx1.net xxx2.net                  ****" << std::endl;
  std::cout << "****************************************************************************" << std::endl;
  exit(1);
}


int main(int argc, char * argv[]) {
  if (argc != 5)
    Usage();

  M_LIST m_list;
  E_LIST e_list;
  /*
  std::string model_dir = "/home/lsx/Data/model库/chain模型/chain_e_dither_0.0";
  std::string output_file = "/home/lsx/work/CA/polly-v2.1-release/Polly/polly/export_lsx/T_OUT.txt";

  std::string net_list_file = "/home/lsx/Data/ZJ_partc_release/ZJ-partC-v2.1.txt";
  */

  std::string type = std::string(argv[1]);
  std::string model_dir = std::string(argv[2]);
  std::string net_list_file = std::string(argv[3]);
  std::string output_file = std::string(argv[4]);

  auto stime = std::chrono::system_clock::now();
  ReadListFile(net_list_file, &m_list);

  ParallelProcess(&m_list, &e_list,type, model_dir, output_file);
  std::cout << "e_list:" << e_list.size() << std::endl;

  for (auto T : e_list) {
    T->join();
  }

  for (auto T : e_list) {
    delete T;
  }

  auto etime = std::chrono::system_clock::now();
  double t = std::chrono::duration_cast<std::chrono::seconds>(etime - stime).count();
  std::cout << "Time:" << t << std::endl;
  return 0;

}


