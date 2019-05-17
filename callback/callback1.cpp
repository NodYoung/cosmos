//
// Created by liyanan on 5/7/19.
// reference: [C++ callback using class member](https://stackoverflow.com/questions/14189440/c-callback-using-class-member)
//            [C++11 styled callbacks?](https://stackoverflow.com/questions/12338695/c11-styled-callbacks)
//            [std::function with non-static member functions](https://stackoverflow.com/questions/10022789/stdfunction-with-non-static-member-functions)
#include <iostream>
#include <functional>
#include <memory>

class ClassB {
public:
    ClassB();
    void on_msg();
    void set_on_msg_callback(std::function<void() > callback);
private:
    std::function<void() > on_msg_callback;
};
ClassB::ClassB() : on_msg_callback(NULL) {}
void ClassB::on_msg() {
    if(on_msg_callback) {
        on_msg_callback();
    }
    else {
        std::cout << "no callback" << std::endl;
    }
}
void ClassB::set_on_msg_callback(std::function<void()> callback) {
    on_msg_callback = callback;
}


class ClassA
{
public:
    ClassA();

    // Note: No longer marked `static`, and only takes the actual argument
    void Callback();
    std::shared_ptr<ClassB> mb;
private:

};

ClassA::ClassA() {
    //mb = std::make_shared<ClassB>();
    mb.reset(new ClassB());
    //mb->set_on_msg_callback(std::bind(&ClassA::Callback, this));
}

void ClassA::Callback() {
    std::cout << "ClassA::Callback " << std::endl;
}

int main() {
    ClassA ca;
    ca.mb->on_msg();
    ca.mb->set_on_msg_callback(std::bind(&ClassA::Callback, ca));
    ca.mb->on_msg();
    return 0;
}

