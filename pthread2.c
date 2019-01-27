#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int first;
	int last;
	int s;
	char* name;
} MY_ARGS;

int arr[5000];
int s = 0;

void* myfunc(void *args){
       int i;
	   MY_ARGS* my_args = (MY_ARGS*)args;
       for(i = my_args->first;i < my_args->last;++i){
           my_args->s += arr[i];
	//	   printf("%s : arr[%d] = %d\n", my_args->name, i, arr[i]);
      }
        return NULL;
}
int main(){
	for(int i = 0;i < 5000;++i){
		arr[i] = rand() % 50;
	}


    pthread_t th1;
	pthread_t th2;

	
	MY_ARGS my_args1 = {0, 2500, 0, "t1"};
	MY_ARGS my_args2 = {2500, 5000, 0, "t2"};


	pthread_create(&th1, NULL, myfunc, &my_args1);
	pthread_create(&th2, NULL, myfunc, &my_args2);
	

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	
	
	printf("s1 = %d\n", my_args1.s);
	printf("s2 = %d\n", my_args2.s);
	printf("s1 + s2 = %d\n", my_args1.s + my_args2.s);
	
	return 0;
}
