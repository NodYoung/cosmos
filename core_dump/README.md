// reference:[GDB 调试 C++ 程序 core dump](https://my.oschina.net/zenglingfan/blog/169871)

ulimit -a
ulimit -c unlimited
g++ -g -std=gnu++0x coreDumpTest.cpp -o coreDumpTest
./coreDumpTest
gdb ./coreDumpTest core


g++ -g coreDumpTest2.cpp -o coreDumpTest2
./coreDumpTest2
gdb ./coreDumpTest2 core
bt
f5
