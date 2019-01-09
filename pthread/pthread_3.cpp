#include<pthread.h>
//#include<stdio.h>
#include<iostream>

pthread_mutex_t count_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var=PTHREAD_COND_INITIALIZER;
int count=0;

// write numbers 1-3 and 8-10 as permitted by func_2
void *func_1(void *x) {
  for(;;) {
    pthread_mutex_lock(&count_mutex);
    //wait while func_2() operates on count
    //mutex unlocked if condition variable in func_2() signaled.
    pthread_cond_wait(&condition_var, &count_mutex);
    count++;
    std::cout << "Counter value func_1: " << count << std::endl;
    pthread_mutex_unlock(&count_mutex);
    if(count>=10) return (void *)0; 
  }
}

// write numbers 4-7 
void *func_2(void *x) {
  for(;;) {
    pthread_mutex_lock(&count_mutex);
    if(count < 3 || count > 6) {
      // condition of if statement has been met.
      // signal to free waiting thread by freeing the mutex.
      // Note: func_1() is now permitted to modify "count".
      pthread_cond_signal(&condition_var);
    }
    else{
      count++;
      std::cout << "Counter value func_2: " << count << std::endl;
    }
    pthread_mutex_unlock(&count_mutex);
    if(count>=10) return (void *)0; 
  }
}


//learn mutex
int main() {
  pthread_t thread_1;
  pthread_t thread_2;
  int x_1=1;
  int x_2=2;
  pthread_create(&thread_1, NULL, func_1, &x_1);
  pthread_create(&thread_2, NULL, func_2, &x_2);
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
  pthread_exit(NULL);
  return 0;
}
