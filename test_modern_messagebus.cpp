//
// Created by liyanan on 8/16/19.
//
#include <iostream>
#include <string>
#include <modern_messagebus.hpp>

void test_messge_bus()
{
    message_bus bus;

    bus.register_handler("test", [](int a, int b) { return a + b; });
    bus.register_handler("void", [] { std::cout << "void" << std::endl; });
    bus.register_handler("str", [](int a, const std::string& b) { return std::to_string(a) + b; });
    bus.register_handler("ptr", [](const char* data, int size) { std::cout << data <<" "<<size<< std::endl; });

    auto r = bus.call<int>("test", 1, 2);
    std::cout << r << std::endl;
    auto s = bus.call<std::string>("str", 1, std::string("test"));
    bus.call_void("void");

    bus.call_void("ptr", "test", 4);
}

message_bus g_bus;
const std::string Topic="Drive";
const std::string CallBackTopic="DriveOk";

struct Subject {
    Subject() {
        g_bus.register_handler(CallBackTopic, [this]{DriveOk();});
    }
    void SendReq(const std::string& topic) {
        g_bus.call_void(topic, 50);
    }
    void DriveOk() {
        std::cout << "drive ok" << std::endl;
    }
};

struct Car {
    Car() {
        g_bus.register_handler(Topic, [this](int speed){Drive(speed);});
    }
    void Drive(int speed) {
        std::cout << "Car drive" << speed << std::endl;
        g_bus.call_void(CallBackTopic);
    }
};

struct Bus {
    Bus() {
        g_bus.register_handler(Topic, [this](int speed){Drive(speed);});
    }
    void Drive(int speed) {
        std::cout << "Bus drive" << speed << std::endl;
        g_bus.call_void(CallBackTopic);
    }
};

struct Truck {
    Truck() {
        g_bus.register_handler(Topic, [this](int speed){Drive(speed);});
    }
    void Drive(int speed) {
        std::cout << "Truck drive" << speed << std::endl;
        g_bus.call_void(CallBackTopic);
    }
};

int main() {
    //test_messge_bus();
    Subject subject;
    Car car;
    Bus bus;
    Truck truck;
    subject.SendReq(Topic);
    subject.SendReq("");
    return 0;
}