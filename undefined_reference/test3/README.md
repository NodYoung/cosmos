gcc -c func.c
gcc -c test.c
ar -rc func.a func.o
ar -rc test.a test.o
gcc -o main main.c test.a  //error
gcc -o main main.c test.a func.a
gcc -o main main.c func.a test.a  //error