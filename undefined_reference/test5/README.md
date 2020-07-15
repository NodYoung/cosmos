gcc -c test.c
ar -rc test.a test.o
g++ -o main main.cpp test.a