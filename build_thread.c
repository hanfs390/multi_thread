#include <stdio.h>
#include <pthread.h>

/* 线程处理函数 */
void *pthread_handler(void *arg){
	int i = 5;

	while(i > 0){
		sleep(1);
		printf("thread\n");
		i--;
	}

	pthread_exit("thread1");
}
int main(int argc, char *argv[])
{
	pthread_t thread;
	/* 创建新线程 */
	void *retval;
	if(pthread_create(&thread, NULL, pthread_handler, NULL) != 0){
		perror("pthread_create error");
		return -1;
	}
	/* 回收退出线程的资源 */
	pthread_join(thread, &retval);
	printf("retval:%s\n", (char *)retval);
	return 0;
}
