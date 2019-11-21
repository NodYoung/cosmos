//
// Created by liyanan on 11/21/19.
//
// Reference:
// [Plugins in CPP: Dynamically Linking Shared Objects](https://github.com/christopherpoole/cppplugin/wiki/Plugins-in-CPP:-Dynamically-Linking-Shared-Objects)
//


#include <iostream>
#include <dlfcn.h>

typedef void (*func_t)();

int main() {
    void * shared_object = dlopen("./test.so", RTLD_LAZY);
    func_t func = (func_t) dlsym(shared_object, "func");

    func();

    dlclose(shared_object);
}