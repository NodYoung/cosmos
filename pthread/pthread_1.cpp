#include<pthread.h>
//#include<stdio.h>
#include<iostream>

void *func(void *x) {
  int xt = *(int *)x;
  std::cout << "Thread Function Start" << std::endl;
  std::cout << "x=" << xt << std::endl;
  std::cout << "Thread Function End" << std::endl;
  return (void *)0;
}

//learn pthread create
int main() {
  pthread_t thread_1;
  pthread_t thread_2;
  int x_1=1;
  int x_2=2;
  pthread_create(&thread_1, NULL, func, &x_1);
  pthread_create(&thread_2, NULL, func, &x_2);
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
  pthread_exit(NULL);
  return 0;
}
