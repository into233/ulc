#include <stdio.h>                                 
#include <stdlib.h>                                
#include <pthread.h>                               
                                                   
void* myfunc(void *argc){                          
       int i;                                     
       for(i = 0;i < 50;++i){                     
           printf("%d\n", i);                 
      }                                          
        return NULL;                               
}                                                  
                                                   
                                                   
                                                   
int main(){                                        
	                                                   
    pthread_t th1;                             
	pthread_t th2;
			                                                   
	pthread_create(&th1, NULL, myfunc, NULL);  							        pthread_create(&th2, NULL, myfunc, NULL);                                           
	pthread_join(th1, NULL);
	return 0;
}
