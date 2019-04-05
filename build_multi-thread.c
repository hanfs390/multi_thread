#include <stdio.h>
#include <pthread.h>

//线程处理函数
void *pthread_handler1(void *arg){
	int i = 5;

	while(i > 0){
		sleep(1);
		printf("thread1\n");
		i--;
	}

	pthread_exit(0);
}
void *pthread_handler2(void *arg){
	int i = 3;

	while(i > 0){
		sleep(1);
		printf("thread2\n");
		i--;
	}

	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	//创建新线程
	if(pthread_create(&thread1, NULL, pthread_handler1, NULL) != 0){
		perror("pthread_create error");
		return -1;
	}
	if(pthread_create(&thread2, NULL, pthread_handler2, NULL) != 0){
		perror("pthread_create error");
		return -1;
	}

	//回收退出线程的资源
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}
