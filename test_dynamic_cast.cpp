//
// Created by liyanan on 6/5/20.
//
#include <iostream>
#include <memory>

class Base
{
public:
    Base() {
        std::cout << "Base" << std::endl;
    }
    virtual ~Base() {
        std::cout << "~Base" << std::endl;
    }

    void UseBase() {
        std::cout << "UseBase" << std::endl;
    }
};

class Derive : public Base
{
public:
    Derive() {
        std::cout << "Derive" << std::endl;
    }
    ~Derive() {
        std::cout << "~Derive" << std::endl;
    }

    void UseDerive() {
        std::cout << "UseDerive" << std::endl;
    }
};



void test1() {
    std::shared_ptr<Base> pbase;
    pbase = std::shared_ptr<Base>(new Derive());
    pbase->UseBase();
    std::shared_ptr<Derive> pderive = std::dynamic_pointer_cast<Derive>(pbase);
    pderive->UseDerive();
    pbase.reset();
    pbase = std::shared_ptr<Base>(new Derive());
}

void test2() {
    std::shared_ptr<Base> pbase;
    std::shared_ptr<Derive> pderive;
    pderive = std::make_shared<Derive>();
    pbase = std::dynamic_pointer_cast<Base>(pderive);
    pbase->UseBase();
}

void test3() {
    std::shared_ptr<Base> pbase;
    std::shared_ptr<Derive> pderive;
    pbase = std::make_shared<Derive>();
    pderive = std::dynamic_pointer_cast<Derive>(pbase);
    if (pderive == NULL) {
        std::cout << "pderive is null" << std::endl;
    }
    pderive->UseDerive();
}

int main() {
    std::cout << "=================test1================" << std::endl;
    test1();
    std::cout << "=================test2================" << std::endl;
    test2();
    std::cout << "=================test3================" << std::endl;
    test3();
    return 0;
}


