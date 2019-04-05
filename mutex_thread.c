#include <stdio.h>
#include <pthread.h>


pthread_mutex_t lock;
int count = 0;
int value1 = 0;
int value2 = 0;
//线程处理函数
void *pthread_handler1(void *arg){
	while(1){
		//上锁
		pthread_mutex_lock(&lock);
		count++;
		value1 = count;
		value2 = count;
		//解锁
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(0);
}
void *pthread_handler2(void *arg){
	while(1){
		//上锁
//		pthread_mutex_lock(&lock);
		if(value1 != value2){
			usleep(30000);
			printf("value1 = %d value2 = %d\n", value1, value2);
		}
		//解锁
//		pthread_mutex_unlock(&lock);
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	//创建新线程
	//初始化互斥锁
	if(pthread_mutex_init(&lock, NULL) != 0){
		perror("pthread_mutex_init error");
		return -1;
	}
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

	pthread_mutex_destroy(&lock);
	return 0;
}
