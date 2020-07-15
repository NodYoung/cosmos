gcc -c test.c
gcc -c main.c
gcc -o main main.o  //error
gcc -o main main.o test.o
gcc -o main main.c test.c