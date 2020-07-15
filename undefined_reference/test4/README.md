gcc -c test.c
ar -rc test.a test.o
gcc -o main main.c test.a  //error